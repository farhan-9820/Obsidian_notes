```python

def reverse_out_of_place(head):
    # Handle empty list case
    if head is None:
        return None
        
    # Line 2: Create the first node of the new list using the head's data
    new_head = Node(head.elem, None)
    
    # Line 3: Start from the second node of the source list
    temp = head.next
    
    # Line 4: Traverse the rest of the source list
    while temp is not None:
        # Line 5: Create a new node that points to the CURRENT new_head
        # This is the "reversing" magic!
        n = Node(temp.elem, new_head)
        
        # Line 6: Update new_head to be this new node
        new_head = n
        
        # Line 7: Move to the next node in the source
        temp = temp.next
        
    # Line 9: Return the head of the reversed list
    return new_head
```



To make **Out-of-Place Reversal** stick, we’re going to build a **Gothic Taxidermy Shop** in your mind. Forget clean code; think of this as a weird biological assembly line.

### The Setup: The Shop of "New Heads"

**The Original List:** Imagine a line of **undead rats** stitched tail-to-nose ($10 \rightarrow 20 \rightarrow 30$).

---

### Step 1: The First Sacrifice (Line 2)

> `new_head = Node(head.elem, None)`

You walk to the first rat in the line ($10$). You don't move him; you **clone his head** and put it on a silver platter. This head has no body yet (`None`).

- **The Mental Image:** A floating, glowing rat head ($10$) sitting on a velvet cushion. This is your `new_head`.
    

---

### Step 2: The Next Victim (Line 3)

> `temp = head.next`

You move your hand to the **second** rat in the original line ($20$). This is your "temporary" target.

- **The Mental Image:** You are pointing a crooked finger at the second rat, who is sweating nervously.
    

---

### Step 3: The Leap-Frog Stitching (Lines 5-6)

> `n = Node(temp.elem, new_head)`
> `new_head = n`

This is where it gets bizarre. You clone the second rat ($20$), but you stitch its "next" pointer directly into the mouth of the floating head on the platter ($10$).

- **The Mental Image:** You grab a fresh rat head ($20$), and its long, purple tongue (the `next` pointer) licks and sticks to the $10$ head.
    
- **The Reversal:** You then declare this new, conjoined monstrosity ($20 \rightarrow 10$) to be the **New King** (`new_head`).
    

---

### Step 4: The Endless Conveyor (Lines 7-8)

> `temp = temp.next`

You move your finger to the next rat in the original line ($30$) and repeat the "tongue-stitch."

- **The Final Image:** Every time you find a new rat, you clone it and make it **eat** the previous "New King."
    
- By the time you’re done, the last rat you saw ($30$) is at the front, holding the entire chain in its mouth.
    

---

### Why this works for your memory:

1. **Out-of-Place:** You never broke the original rats; you just made clones (New Nodes).
    
2. **The `next` logic:** By pointing the _new_ node's `next` to the _old_ `new_head`, you are building the list **backwards** like a stack of plates.
    
3. **The `new_head` update:** The "King" is always the last head you touched.
    

**Does that creepy rat shop help the logic click, or should we try a different "palace" for the In-Place reversal?**