#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_PROCESSES 64
#define MAX_THREADS   64
#define SNAP_SIZE     4096

#define RUNNING 1
#define WAITING 2
#define ZOMBIE  3


struct pcb {
    int   pid;
    int   ppid;
    int   state;               
    int   exit_status;
    int   children[MAX_PROCESSES];
    int   num_children;
    int   waiting_for;        
    sem_t wait_sem;           
};


static struct pcb process_table[MAX_PROCESSES];
static int next_pid = 2;                        //since the first pid is already 1 , I have defined it to 2 

static pthread_mutex_t pt_mutex;


static char pending_snap[SNAP_SIZE];
static sem_t monitor_sem;
static sem_t monitor_done_sem;
static int system_done = 0;  

static int find_idx(int pid)
{
    int i;
    for (i = 0; i < MAX_PROCESSES; i++)
        if (process_table[i].state != 0 && process_table[i].pid == pid)
            return i;
    return -1;
}


static int free_slot(void)
{
    int i;
    for (i = 0; i < MAX_PROCESSES; i++)
        if (process_table[i].state == 0)
            return i;
    return -1;
}


static void remove_child(int pi, int cpid)                          //we are just shifting the array of children inside the pcb of that process from the process table
{
    int i, j;
    for (i = 0; i < process_table[pi].num_children; i++) {
        if (process_table[pi].children[i] == cpid) {
            for (j = i; j < process_table[pi].num_children - 1; j++)
                process_table[pi].children[j] = process_table[pi].children[j + 1];
            process_table[pi].num_children--;
            return;
        }
    }
}


static void build_snap(const char *label)
{
    int  i;
    char line[128];          //local buffer, temp workspace 

    pending_snap[0] = '\0';                                //empties the string by putting a null terminator inside the string
    strcat(pending_snap, label);
    strcat(pending_snap, "\n");
    strcat(pending_snap, "PID\t\tPPID\t\tSTATE\t\tEXIT_STATUS\n");
    strcat(pending_snap, "----------------------------------------------\n");

    for (i = 0; i < MAX_PROCESSES; i++) {
        struct pcb *p = &process_table[i];                    //aliasing (it points to the current locker) , cpu doesnt have to calculate p , we manually write it down
        char *st;
        if (p->state == 0) continue;    // this skips the terminated slots 
        st = (p->state == RUNNING) ? "RUNNING" :
             (p->state == WAITING) ? "WAITING" : "ZOMBIE";
        if (p->state == ZOMBIE)
            sprintf(line, "%d\t\t%d\t\t%s\t\t%d\n",
                    p->pid, p->ppid, st, p->exit_status);              //if the process is dead but not yet reaped, it prints the actual `exit_status`.
        else
            sprintf(line, "%d\t\t%d\t\t%s\t\t-\n",
                    p->pid, p->ppid, st);                               //if the process is still alive, the `exit_status` is irrelevant, so it prints a hyphen `-`
        strcat(pending_snap, line);                                    
    }
}


static void send_snap(void)
{
    sem_post(&monitor_sem);
    sem_wait(&monitor_done_sem); 
}


static void *monitor_func(void *arg)
{
    FILE *fp = fopen("snapshots.txt", "w");
    char  local[SNAP_SIZE];
    (void)arg;

    while (1) {
        sem_wait(&monitor_sem);
        if (system_done) break;

        strcpy(local, pending_snap);
        sem_post(&monitor_done_sem);

        fputs(local, fp);
        fputs("\n", fp);
    }

    fclose(fp);
    pthread_exit(NULL);
}


static void pm_fork(int parent_pid, int thread_id)
{
    int  pi, si, cpid;
    char label[128];

    sprintf(label, "Thread %d calls pm_fork %d", thread_id, parent_pid);

    pthread_mutex_lock(&pt_mutex);

    pi = find_idx(parent_pid);
    si = free_slot();
    if (pi == -1 || si == -1 || process_table[pi].state != RUNNING) {
        pthread_mutex_unlock(&pt_mutex);
        return;
    }

    cpid = next_pid++;
    process_table[si].pid = cpid;
    process_table[si].ppid = parent_pid;
    process_table[si].state = RUNNING;
    process_table[si].exit_status = -1;
    process_table[si].num_children = 0;
    process_table[si].waiting_for = 0;
    sem_init(&process_table[si].wait_sem, 0, 0);

    process_table[pi].children[process_table[pi].num_children++] = cpid;
    build_snap(label);
    send_snap();                     
    pthread_mutex_unlock(&pt_mutex);
}


static void reparent_children(int dying_idx)
{
    int i, init_idx;
    init_idx = find_idx(1); 
    if (init_idx == -1) return;

    for (i = 0; i < process_table[dying_idx].num_children; i++) {
        int cpid = process_table[dying_idx].children[i];
        int ci   = find_idx(cpid);
        if (ci == -1) continue;

        process_table[ci].ppid = 1;
        process_table[init_idx].children[process_table[init_idx].num_children++] = cpid;

        if (process_table[ci].state == ZOMBIE) {
            process_table[ci].state = 0;
            process_table[init_idx].num_children--;
        }
    }
    process_table[dying_idx].num_children = 0;
}


static void do_exit(int pid, int status, int thread_id, int is_kill)
{
    int ci, pi, wake;
    sem_t *psem;
    char label[128];

    if (is_kill)
        sprintf(label, "Thread %d calls pm_kill %d", thread_id, pid);
    else
        sprintf(label, "Thread %d calls pm_exit %d %d", thread_id, pid, status);

    wake = 0;
    psem = NULL;

    pthread_mutex_lock(&pt_mutex);

    ci = find_idx(pid);
    if (ci == -1) { pthread_mutex_unlock(&pt_mutex); return; }
    reparent_children(ci);
    pi = find_idx(process_table[ci].ppid);

    if (pi != -1 && process_table[pi].state == WAITING &&
        (process_table[pi].waiting_for == -1 ||
         process_table[pi].waiting_for == pid)) {
        
        process_table[ci].state = 0;
        process_table[pi].state = RUNNING;
        remove_child(pi, pid);
        psem = &process_table[pi].wait_sem;
        wake = 1;
    } else {

        process_table[ci].state       = ZOMBIE;
        process_table[ci].exit_status = status;
    }

    build_snap(label);
    send_snap();
    pthread_mutex_unlock(&pt_mutex);

    if (wake) sem_post(psem);
}

static void pm_exit(int pid, int status, int thread_id) { do_exit(pid, status, thread_id, 0); }
static void pm_kill(int pid, int thread_id) { do_exit(pid, -1, thread_id, 1); }


static void pm_wait(int parent_pid, int child_pid, int thread_id)
{
    int pi, i, zi, zpid;
    sem_t *my_sem;
    char label[128];

    sprintf(label, "Thread %d calls pm_wait %d %d", thread_id, parent_pid, child_pid);

    pthread_mutex_lock(&pt_mutex);

    pi = find_idx(parent_pid);

    if (pi == -1 || process_table[pi].num_children == 0) {
        pthread_mutex_unlock(&pt_mutex);
        return;
    }

    zi = -1; zpid = -1;
    for (i = 0; i < process_table[pi].num_children; i++) {
        int c  = process_table[pi].children[i];
        int ci = find_idx(c);
        if (ci != -1 && process_table[ci].state == ZOMBIE &&
            (child_pid == -1 || process_table[ci].pid == child_pid)) {
            zi = ci; zpid = c; break;
        }
    }

    if (zi != -1) {
        reparent_children(zi);
        process_table[zi].state = 0;
        remove_child(pi, zpid);
        build_snap(label);
        send_snap();
        pthread_mutex_unlock(&pt_mutex);
        return;
    }

    if (child_pid != -1) {
        int found = 0;
        for (i = 0; i < process_table[pi].num_children; i++)
            if (process_table[pi].children[i] == child_pid) { found = 1; break; }
        if (!found) { pthread_mutex_unlock(&pt_mutex); return; }
    }

    process_table[pi].state       = WAITING;
    process_table[pi].waiting_for = child_pid;
    my_sem = &process_table[pi].wait_sem;

    build_snap(label);
    send_snap();                  
    pthread_mutex_unlock(&pt_mutex);
    sem_wait(my_sem);
}


typedef struct { int id; char filename[256]; } ThreadArg;

static void *worker_func(void *arg)
{
    ThreadArg *targ = (ThreadArg *)arg;
    FILE *fp = fopen(targ->filename, "r");
    char line[256], cmd[64];

    if (!fp) pthread_exit(NULL);

    while (fgets(line, sizeof(line), fp)) {
        if (sscanf(line, "%63s", cmd) != 1) continue;

        if (strcmp(cmd, "fork") == 0) {
            int pid;
            sscanf(line, "%*s %d", &pid);
            pm_fork(pid, targ->id);

        } else if (strcmp(cmd, "exit") == 0) {
            int pid, status;
            sscanf(line, "%*s %d %d", &pid, &status);
            pm_exit(pid, status, targ->id);

        } else if (strcmp(cmd, "wait") == 0) {
            int ppid, cpid;
            sscanf(line, "%*s %d %d", &ppid, &cpid);
            pm_wait(ppid, cpid, targ->id);

        } else if (strcmp(cmd, "kill") == 0) {
            int pid;
            sscanf(line, "%*s %d", &pid);
            pm_kill(pid, targ->id);

        } else if (strcmp(cmd, "sleep") == 0) {
            int ms;
            sscanf(line, "%*s %d", &ms);
            usleep((unsigned int)ms * 1000);
        }
        
    }

    fclose(fp);
    pthread_exit(NULL);
}


int main(int argc, char *argv[])
{
    int       i, nw;
    pthread_t monitor_th;
    pthread_t threads[MAX_THREADS];
    ThreadArg targs[MAX_THREADS];

    if (argc < 2) return 0;
    nw = argc - 1;

    pthread_mutex_init(&pt_mutex, NULL);
    sem_init(&monitor_sem,      0, 0);
    sem_init(&monitor_done_sem, 0, 0);

    for (i = 0; i < MAX_PROCESSES; i++)
        process_table[i].state = 0;

    process_table[0].pid          = 1;
    process_table[0].ppid         = 0;
    process_table[0].state        = RUNNING;
    process_table[0].exit_status  = -1;
    process_table[0].num_children = 0;
    process_table[0].waiting_for  = 0;
    sem_init(&process_table[0].wait_sem, 0, 0);

    pthread_create(&monitor_th, NULL, monitor_func, NULL);
    pthread_mutex_lock(&pt_mutex);
    build_snap("Initial Process Table");
    send_snap();
    pthread_mutex_unlock(&pt_mutex);

    for (i = 0; i < nw; i++) {
        targs[i].id = i;
        strcpy(targs[i].filename, argv[i + 1]);
        pthread_create(&threads[i], NULL, worker_func, &targs[i]);
    }

    for (i = 0; i < nw; i++)
        pthread_join(threads[i], NULL);

    system_done = 1;
    sem_post(&monitor_sem);
    pthread_join(monitor_th, NULL);

    pthread_mutex_destroy(&pt_mutex);
    sem_destroy(&monitor_sem);
    sem_destroy(&monitor_done_sem);

    return 0;
}