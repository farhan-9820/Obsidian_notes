This `main` function is the **"Orchestrator"** of your entire system. It is responsible for setting up the environment, launching the threads, and performing a clean shutdown.

Think of it like a **theater production**: `main` builds the stage, hires the actors (Worker threads) and the cameraman (Monitor thread), and once the play is over, it turns off the lights.

---

### Low-Level Breakdown of `main`

#### 1. Resource Initialization

C

```
pthread_mutex_init(&pt_mutex, NULL);
sem_init(&monitor_sem,      0, 0);
sem_init(&monitor_done_sem, 0, 0);
```

- **Mutex:** Sets the lock for the process table to "Unlocked."
    
- **Semaphores:** Sets both communication signals to 0. This means the Monitor thread will **immediately sleep** when it starts because there are no signals yet.
    

#### 2. Creating "The First Process" (PID 1)

C

```
process_table[0].pid = 1;
process_table[0].state = RUNNING;
```

Every OS needs a starting point. In Linux, this is `init`. Here, you manually create the first entry so that when worker threads call `fork`, they have a parent to start from.

#### 3. Launching the Monitor

C

```
pthread_create(&monitor_th, NULL, monitor_func, NULL);
```

The "Cameraman" (Monitor) starts first so it is ready to record the very first state of the OS.

#### 4. Spawning the Workers

C

```
for (i = 0; i < nw; i++) {
    pthread_create(&threads[i], NULL, worker_func, &targs[i]);
}
```

If you pass 3 files in the command line (`./sim file1.txt file2.txt file3.txt`), `main` creates **3 separate worker threads**. Each one reads its own file simultaneously.

#### 5. The "Clean Exit" (The Kick)

C

```
system_done = 1;
sem_post(&monitor_sem); // The "Last Kick" we discussed!
pthread_join(monitor_th, NULL);
```

Once all worker threads finish (`pthread_join`), the system is done. `main` sets the flag and "kicks" the monitor one last time so it can see the flag and exit safely.

---

### The Whole Project Workflow: "The Life of a Command"

To understand the project as a whole, let's trace a single command from a script file (e.g., `fork 1`).

1. **Reading:** A **Worker Thread** reads `fork 1` from its text file in `worker_func`.
    
2. **Requesting Access:** The worker calls `pm_fork`. The first thing it does is `pthread_mutex_lock`. If another worker is already in there, this thread **blocks**.
    
3. **Executing:** Once it has the lock, it finds a free slot, assigns a new PID, and updates the "Family Tree" in the `process_table`.
    
4. **Preparing the Snapshot:** While still holding the lock, it calls `build_snap`. This creates a text string of the _entire_ current table.
    
5. **Signaling the Monitor:**
    
    - Worker calls `sem_post(&monitor_sem)` $\rightarrow$ This wakes the **Monitor Thread**.
        
    - Worker calls `sem_wait(&monitor_done_sem)` $\rightarrow$ The **Worker pauses**.
        
6. **Recording:**
    
    - **Monitor** wakes up, copies the snapshot to its `local` buffer.
        
    - **Monitor** calls `sem_post(&monitor_done_sem)` $\rightarrow$ This tells the Worker "I got it!"
        
    - **Monitor** writes the data to `snapshots.txt` in the background.
        
7. **Finishing:**
    
    - **Worker** wakes up, calls `pthread_mutex_unlock`.
        
    - The "Kitchen" is now open for the next worker.
        

---

### 🥊 Final Viva "Boss" Question

You have `pthread_mutex_destroy` and `sem_destroy` at the very end.

**Why is it important to "destroy" these resources? What would happen if a program creating thousands of mutexes never destroyed them before closing?** (Hint: It’s related to "Memory Leaks," but specifically for OS kernel resources).

---

### 🥊 Final Viva "Boss" Question 2

Look at the `pthread_join(threads[i], NULL);` loop.

**If one worker thread gets stuck in an infinite loop or a deadlock, what happens to the `main` function? Will the `snapshots.txt` file ever be closed correctly?** (Think: Does `main` move past the `join` if a thread is still running?)