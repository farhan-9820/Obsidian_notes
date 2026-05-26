
![[pm_sim.c]]


1. what is define in C ? 
	1. In C programming, **`#define`** is ==a **preprocessor directive** used to create macros==—named identifiers that the preprocessor replaces with specific values or code fragments before actual compilation begins 
	2. **No Memory Allocation:** Unlike variables (e.g., `int x = 5;`), macros defined with `#define` do not occupy any memory at runtime
	3. 
2. what is struct? 
	1. a user-defined data type that allows you to group variables of different data types under a single name
	2. ```
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
		```

	Members are accessed using the **dot operator (`.`)** for variables and the [[**arrow operator (`->`)**]] for pointers
1. what is the arrow operator? 
	1. used to access the members of a structure or union through a pointer
	2.  It allows you to interact with structure elements when you only have the memory address (pointer) of that structure, rather than the structure variable itself.
	3. **Equivalent Expression:** The expression `ptr->member` is functionally identical to `(*ptr).member`. The parentheses are required in the second version because the [dot operator](https://www.geeksforgeeks.org/c/operators-in-c/) has higher precedence than the dereference operator
2. **static pthread_mutex_t pt_mutex**;
	1. The `static` Keyword: Memory Layout

		When you declare a mutex as `static`, you are making two primary decisions regarding its physical existence in your computer's RAM:

		**Scope (Internal Linkage):** The symbol `pt_mutex` is only visible to the object file (.o) where it is defined. The linker won't let other files "see" it, preventing name collisions.
    
		**Storage Duration:** It is stored in the **`.bss`** (Block Started by Symbol) section of your program's memory. Because it is uninitialized, the OS zero-fills this memory when the program loads
	
	2.  The Data Structure: pthread_mutex_t
		This isn't just a simple integer. On most Linux systems (using NPTL), pthread_mutex_t is a union (usually 24 or 40 bytes) containing a structure called __pthread_mutex_s.

		At the lowest level, it contains:
		
		==The Lock Word== (__lock): A 32-bit integer that represents the state (0 for unlocked, 1 for locked).
		
		==The Waiter Count==: Tracks how many threads are currently "sleeping" while waiting for this specific lock.
		
		==Owner ID==: The Thread ID (TID) of the thread that currently holds the lock (used for recursion checks).
		
		The Futex Word: The specific memory address that the kernel monitors.
	
	3. The Low-Level "Magic": Atomic OperationsWhen you call **pthread_mutex_lock(&pt_mutex),** the CPU doesn't just do a *"read then write."* That would cause a race condition. Instead, it uses **Atomic Instructions**.On x86_64 architecture, this usually involves the LOCK prefix with an instruction like CMPXCHG (Compare and Exchange).$$\text{TargetValue} = \text{CompareExchange}(\text{Address}, \text{Expected}, \text{NewValue})$$The Fast Path: The CPU tries to atomically flip the lock bit from 0 to 1. If it succeeds, the thread continues immediately without ever talking to the Operating System. This takes only a few nanoseconds.The Slow Path (The Futex): If the bit is already 1, the thread cannot proceed. It executes a syscall (system call) to the kernel, specifically futex() (Fast Userspace Mutex).

[[process table and struct pcb]]

[[sprintf]]

[[escape operator in C ]]

[[semaphore and mutex workflow in this project]]

1. [[static int find_idx(int pid)]]
2. [[static int free_slot(void)]]
3. [[static void remove_child(int pi, int cpid)]]
4. [[static void build_snap()]]
5. [[static void send_snap(void)]]
6. [[static void 'monitor_func(void 'arg)]]
7. [[static void pm_fork(int parent_pid, int thread_id)]]
8. [[static void reparent_children(int dying_idx)]]
9. [[static void do_exit(int pid, int status, int thread_id, int is_kill)]]
10. [[static void pm_exit(int pid, int status, int thread_id)]]
11. [[static void pm_kill(int pid, int thread_id)]]
12. [[static void pm_wait(int parent_pid, int child_pid, int thread_id)]]
13. [[worker func]]
14. [[main ()]]


