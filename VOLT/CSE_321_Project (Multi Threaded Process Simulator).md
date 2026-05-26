To tackle this, you should separate the "Logic" (how a kernel manages data) from the "Concurrency" (how multiple threads talk to each other). Since you are already comfortable with low-level systems and C, this approach follows a logical progression from data structures to synchronization.

### Level 1: The Blueprint (Data Structures)

Before writing any thread code, define what a "Process" looks like in your memory.

- **The PCB Struct:** Create a `struct` that holds the PID, PPID, State (an `enum`), and `exit_status`.
    
- **The Process Table:** Define a global array of these structs with a maximum size of 64.
    
- **Initial State:** Your `main` function must manually "seed" the table with PID 1 (the `init` process) before any scripts run.
    

### Level 2: The Core API (Single-Threaded Logic)

Write the functions `pm_fork`, `pm_exit`, and `pm_ps` as if only one person were using them.

- **`pm_fork(parent_pid)`**: Search the array for an empty slot, assign a new PID, and link it to the parent.
    
- **`pm_exit(pid, status)`**: Find the process, change its state to `ZOMBIE`, and save the status.
    
- **`pm_ps()`**: Loop through the array and print any process that isn't in the `TERMINATED` state.
    

### Level 3: The Engine (Script Interpreter & Workers)

Now, make the program dynamic by handling the command-line arguments.

- **The Interpreter:** Write a function that uses `fgets` and `sscanf` to parse lines like `fork 1` or `sleep 200`.
    
- **Worker Creation:** In `main`, use a loop to create one `pthread` for every script file passed in the arguments. Pass the filename to the thread's start routine.
    

### Level 4: The Shield (Synchronization)

This is where you protect the Process Table from "Race Conditions."

- **The Global Mutex:** Every time a function (like `pm_fork`) touches the Process Table array, it **must** lock a `pthread_mutex_t` first and unlock it after.
    
- **The Monitor Signal:** Inside your modification functions, use `pthread_cond_signal` to wake up the **Monitor Thread** so it knows it is time to write to `snapshots.txt`.
    

### Level 5: The "Wait" Logic (Advanced Synchronization)

This is the hardest part. `pm_wait(parent, child)` requires a thread to stop until a specific condition is met.

- **Condition Variables:** Use `pthread_cond_wait`. The Worker Thread should sleep if the child is still `RUNNING` and only wake up when `pm_exit` signals that a process has turned into a `ZOMBIE`.
    

---

### Resources for Inspiration

Since you are a CS student interested in OS architecture, these resources will give you the "C idiom" for this type of work:

- **"Operating Systems: Three Easy Pieces" (OSTEP) by Remzi Arpaci-Dusseau:** Read the chapters on **Threads: API** and **Condition Variables**. It is free online and has the best "how-to" for the `wait/exit` logic.
    
- **"The Linux Programming Interface" by Michael Kerrisk:** Specifically Chapter 30 (Threads: Customization and Detaching). It is the "Bible" of system-level C.
    
- **Beej's Guide to Network Programming:** Even though it’s for networking, his section on **Common Scenarios with Mutexes** is incredibly clear for beginners.
    

### A Quick Tip for your `snapshots.txt`

The assignment says the Monitor Thread should **not** poll (constantly check) the table. Make sure you use a dedicated Condition Variable that specifically tells the Monitor: _"The table just changed; wake up and print!"_

Since you've worked with CPU registers and system calls before, would you like to see how to structure the `pm_wait` logic specifically using condition variables?







[[main_project code question and answers]]
