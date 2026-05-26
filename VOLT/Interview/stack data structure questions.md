
---

## Part 1: The "Architect" Questions (Theory)

### Q1: Why would we use a Stack instead of a List if a List can do everything a Stack does?

**The Answer:** It’s about **Intent** and **Safety**. A Stack provides a "Restricted Interface." By using a Stack, you guarantee that no other part of the program can accidentally modify an element in the middle of the collection. It communicates to other developers: "This data must be processed in LIFO order."

### Q2: What is "Stack Overflow," and how does it differ from "Stack Underflow"?

**The Answer:** * **Stack Overflow:** Occurs when you try to push an item onto a stack that has a fixed size and is already full. In modern Python, this usually happens with the **Call Stack** during infinite recursion.

- **Stack Underflow:** Occurs when you try to `pop()` or `peek()` from an empty stack.
    

---

## Part 2: The "Performance" Questions (Complexity)

### Q3: What is the Time Complexity of reversing an array using a Stack?

**The Answer:** It is **$O(n)$**. You iterate through the array once to `push` everything ($O(n)$), and then iterate once more to `pop` everything back out ($O(n)$). Since $n + n = 2n$, we drop the constant, leaving us with $O(n)$.

### Q4: In terms of Space Complexity, what is the cost of using a Stack for a depth-first search (DFS)?

**The Answer:** **$O(V)$**, where $V$ is the number of vertices (or the depth of the tree). You must store the path of nodes you are currently exploring.

---

## Part 3: The "Whiteboard" Questions (Algorithmic)

### Q5: How can you implement a Queue using two Stacks?

**The Answer:** Since a Stack is LIFO and a Queue is FIFO, you use the second stack to "reverse" the order.

1. **Enqueue:** Push onto `Stack1`.
    
2. **Dequeue:** If `Stack2` is empty, pop everything from `Stack1` and push it into `Stack2`. Then, pop from `Stack2`.
    

### Q6: How would you design a "Min-Stack" that retrieves the minimum element in $O(1)$ time?

**The Answer:** You maintain **two** stacks.

- **Stack A:** Stores all the actual values.
    
- **Stack B (The Min-Stack):** Only stores the minimum value encountered _so far_ at that height.
    
    When you push a value `x`, you also push `min(x, current_min)` onto Stack B. This way, the top of Stack B always knows the minimum value for the current stack height.
    

---

### Part 4: The "Final Boss" Challenge

**Question:** "Given a string containing just the characters `(`, `)`, `{`, `}`, `[` and `]`, determine if the input string is valid."

**How to solve it with a Stack:**

1. Iterate through the string.
    
2. If you see an **opening** bracket, `push` it onto the stack.
    
3. If you see a **closing** bracket, `pop` the top of the stack and check if it matches (e.g., if you see `}`, the popped item must be `{`).
    
4. If the stack is empty at the end, the string is valid. If it's not empty (or you found a mismatch), it's invalid.
    

---

Let’s crank up the difficulty. These 5 questions focus on real-world stack applications and some tricky "gotchas" that separate beginners from seniors.

---

## 1. The "Function Call" Question

### Q: How does the computer use a Stack to handle function calls (The Call Stack)?

**The Answer:** When a function is called, the system creates an **Activation Record** (or Frame) containing the function's local variables and return address, and **pushes** it onto the Call Stack. When the function finishes, its frame is **popped**, and the CPU knows exactly where to return to in the previous function. This is why deep recursion causes a `StackOverflowError`.

---

## 2. The "Undo/Redo" Logic

### Q: How would you implement an "Undo" and "Redo" feature in a text editor using Stacks?

**The Answer:** You use **two stacks**:

1. **Undo Stack:** Every time the user types or deletes, you push that action onto this stack.
    
2. **Redo Stack:** When the user hits "Undo," you pop the action from the Undo Stack, reverse it, and **push** it onto the Redo Stack.
    
3. If the user performs a _new_ action, you must clear the Redo Stack.
    

---

## 3. The "Postfix" (RPN) Algorithm

### Q: How do you evaluate a Postfix expression (e.g., `3 4 + 5 *`) using a stack?

**The Answer:** 1. Iterate through the tokens.

2. If it's a **number**, push it.

3. If it's an **operator** (like `+`), pop the top two numbers, apply the operator ($3 + 4 = 7$), and push the result ($7$) back onto the stack.

4. At the end, the only number remaining on the stack is the total result ($7 \times 5 = 35$).

---

## 4. The "Sorting" Constraint

### Q: Can you sort a stack using only one additional temporary stack?

**The Answer:** Yes. It's an $O(n^2)$ logic.

1. Pop an element from the `Original Stack` and call it `temp`.
    
2. While the `Temporary Stack` is not empty and its top is **greater** than `temp`:
    
    - Pop from `Temporary Stack` and push it back to `Original Stack`.
        
3. Push `temp` into the `Temporary Stack`.
    
4. Repeat until the `Original Stack` is empty.
    

---

## 5. The "Monotonic Stack" Concept

### Q: What is a Monotonic Stack, and when would you use it?

**The Answer:** A Monotonic Stack is a stack where elements are always in increasing or decreasing order. You use it to solve the **"Next Greater Element"** problem. As you iterate through an array, you pop elements from the stack that are smaller than the current element—this tells you that the current element is the "next greater" one for all those popped items.

---

### Your Mock Interview Performance Review

- **If you knew 4-5:** You're ready for Mid-level developer interviews.
    
- **If you knew 2-3:** You have the basics, but need to practice "Stack-based algorithms" (Postfix, Balancing, etc.).
    
- **If you knew 0-1:** Go back to the "Tower of Hats" memory palace and focus on how the `pop` and `push` actions change the data.
    
