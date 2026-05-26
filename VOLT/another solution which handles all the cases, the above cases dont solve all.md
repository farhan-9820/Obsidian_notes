

![[Pasted image 20260405082851.png]]



This algorithm is a classic "Fairness" wrapper around the `compare_and_swap` (CAS) instruction. While CAS by itself handles **Mutual Exclusion**, it doesn't guarantee **Bounded Waiting**—a fast process could keep stealing the lock. This specific implementation uses a "waiting array" to act like a **polite queue**.

---

### 1. The Entry Section (The Waiting Room)

C

```
waiting[i] = true;
key = 1;
while (waiting[i] && key == 1)
    key = compare_and_swap(&lock, 0, 1);
waiting[i] = false;
```

- **The Intent:** Process $P_i$ raises its hand (`waiting[i] = true`) to show it wants in.
    
- **The CAS Check:** It tries to swap the `lock` from 0 to 1.
    
    - If `lock` was 0, `compare_and_swap` returns 0, `key` becomes 0, and the loop breaks.
        
    - If someone else holds the lock, it keeps spinning.
        
- **The "Secret Door":** Notice the `while` condition checks `waiting[i]`. Even if $P_i$ fails the CAS, it can still enter if **another process** sets its `waiting[i]` to `false`. This is the key to fairness.
    

---

### 2. The Exit Section (The Hand-off)

This is where the magic of **Bounded Waiting** happens. Instead of just releasing the lock and letting everyone "race" for it again, $P_i$ looks for the next person in line.

C

```
j = (i + 1) % n;
while ((j != i) && !waiting[j])
    j = (j + 1) % n;
```

- **The Search:** $P_i$ scans the `waiting` array starting from the person right next to it ($i+1$) in a circular fashion.
    
- **The Selection:** It stops at the first person $P_j$ who is actually waiting (`waiting[j] == true`).
    

---

### 3. Granting Entry (The Deciding Factor)

C

```
if (j == i)
    lock = 0;
else
    waiting[j] = false;
```

- **Case 1 (No one else is waiting):** If the loop goes all the way around back to $i$, it means no other process wants in. $P_i$ sets `lock = 0`, making the critical section available for the next newcomer.
    
- **Case 2 (Found a waiter):** If it finds $P_j$, it sets `waiting[j] = false`.
    
    - **Crucial Logic:** Notice it **does not** set `lock = 0` here. The lock stays at 1. By flipping $P_j$'s waiting flag, $P_j$ "wakes up" and enters its critical section immediately. $P_j$ essentially "inherits" the lock directly from $P_i$.
        

---

### How it satisfies the 3 Requirements:

|**Requirement**|**How this code achieves it**|
|---|---|
|**Mutual Exclusion**|Only one process can get `key == 0` (via CAS) or have its `waiting` flag set to `false` by a departing process at any given time.|
|**Progress**|When a process leaves, it _must_ either reset the lock or pass the baton to a waiting neighbor. It cannot block others if it isn't interested in re-entering.|
|**Bounded Waiting**|Because the exit scan is **circular**, every process $P_k$ is guaranteed to be "checked" by a departing process. You can wait at most $n-1$ turns before the "searchlight" hits your index in the array.|

---

### Memory Palace: The Revolving Restaurant

Imagine a circular restaurant with one private dining room (the Critical Section).

1. **Entry:** You stand at your numbered spot and press a button (`waiting[i] = true`).
    
2. **The Lock:** You try to grab the one available key.
    
3. **The Exit:** When the person inside finishes, they don't just throw the key on the floor. They walk out and look at the spots starting from their right. The **very first** person they see with their button pressed, they walk over and hand them a "VIP Pass" (`waiting[j] = false`) to go straight in.
    
4. **Result:** No matter how fast or "high priority" someone else is, they can't jump the circular line. Everyone gets their turn in order.