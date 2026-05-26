This function is the **"Family Tree Surgeon."** When a process is finally "reaped" (completely removed from the system), it shouldn't be listed as a child of its parent anymore. This function finds that specific child in the parent's list and deletes them while keeping the list tidy.

---

### Low-Level Breakdown

#### 1. The Inputs

- **`int pi`**: The **Parent Index** (where the parent is in the process table).
    
- **`int cpid`**: The **Child PID** we want to remove.
    

#### 2. The Search (The first `for` loop)

C

```
for (i = 0; i < process_table[pi].num_children; i++)
```

It looks through the parent's `children[]` array. It only checks up to `num_children`, so it doesn't waste time checking empty slots.

#### 3. The Match

C

```
if (process_table[pi].children[i] == cpid)
```

Once it finds the index `i` where the child's PID matches, it prepares to delete it.

#### 4. The "Shift" (The second `for` loop)

In C, you can't just "delete" an element from the middle of an array and leave a hole. You have to shift everything after it one spot to the left.

C

```
for (j = i; j < process_table[pi].num_children - 1; j++)
    process_table[pi].children[j] = process_table[pi].children[j + 1];
```

- Imagine children at indexes: `[ChildA, ChildB, ChildC, ChildD]`
    
- If we remove `ChildB`, the code moves `ChildC` into `ChildB`'s spot, and `ChildD` into `ChildC`'s spot.
    

#### 5. The Cleanup

C

```
process_table[pi].num_children--;
```

Finally, it reduces the count of children by one. The parent now officially has one less child to track.

---

### Why this is "Viva Critical"?

The examiner might ask: _"Why are you shifting the elements? Why not just set the child's PID to 0 and leave it there?"_

**Your Answer:** To keep the `children[]` array **contiguous** (no gaps). If we left gaps, every other function (like `pm_wait` or `pm_ps`) would have to check every single slot in the array every time, which is inefficient. Shifting ensures the active children are always at the start of the array.

---

### 🥊 Viva Pop Quiz

You just answered a previous question saying `free_slot` looks for `state == 0`.

**In your `remove_child` function, does it change the child's `state` to `0`? Or does it only update the parent's list? If it only updates the list, which function is responsible for finally setting the child's state to `0` (TERMINATED) so its slot can be reused?**