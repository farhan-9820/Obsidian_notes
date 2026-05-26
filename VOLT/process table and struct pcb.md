
In C, when you define `static struct pcb process_table[MAX_PROCESSES];`, you are creating a **contiguous block of memory** large enough to hold 64 copies of the `pcb` struct.

### The Mental Model: The Filing Cabinet

Think of the `process_table` as a **filing cabinet with 64 drawers**.

- **The Array (`process_table`)**: This is the whole cabinet.
    
- **The Index (`pi`)**: This is the specific drawer number (from 0 to 63).
    
- **The Element (`process_table[pi]`)**: This is the **entire folder** (the PCB) inside that specific drawer.
    
- **The Attribute (`.num_children`)**: This is one specific piece of paper inside that folder.
    

### Breaking down `process_table[pi].num_children`

1. **`process_table`**: Go to the global array.
    
2. **`[pi]`**: Offset into the memory to find the $pi^{th}$ PCB.
    
3. **`.num_children`**: Inside that specific PCB, look at the integer value stored in the `num_children` field.
    

Since every single element in the array is of type `struct pcb`, **every single slot (0–63)** has its own private `pid`, its own `state`, and its own `children` array.

---

### Important Global Variables for your Viva

#### 1. The Mutex (`pt_mutex`)

- **Why it's there**: Since multiple worker threads are running at once, they might all try to call `free_slot` or `find_idx` at the same time.
    
- **Low-Level Impact**: If two threads find the same "free slot" at the same time, they will both try to write their new process into the same memory, causing a crash or "Race Condition." You use this mutex to lock the cabinet before any thread opens a drawer.
    

#### 2. The Next PID (`next_pid = 2`)

- You correctly noted that the "Init" process (PID 1) is created manually. This variable ensures that every new process gets a **unique** ID number, regardless of which locker (index) it sits in.
    

#### 3. The Monitor Semaphores (`monitor_sem`)

- This is how your **Monitor Thread** sleeps.
    
- The worker threads will "post" (signal) this semaphore whenever they change something. It’s like a bell that rings to tell the monitor: "Hey, I changed the table! Wake up and take a snapshot!".
    

---

### 🥊 Viva Pop Quiz

Look at your `struct pcb`. You have an array **inside** an array:

`int children[MAX_PROCESSES];` inside `process_table[MAX_PROCESSES];`.

**If the OS needs to find the 3rd child of the process sitting at index 5, what would the C code look like to access that specific child's PID? (Hint: Use two sets of square brackets).**

process_table[5].children[3]