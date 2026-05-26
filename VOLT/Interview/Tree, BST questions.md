Moving into Trees and Binary Search Trees (BSTs) is where interviewers test your ability to think **recursively**. In a Tree, every node is the "root" of its own smaller subtree.

Here are 10 essential questions to prepare you for a technical round.

---

### 1. Tree vs. Binary Search Tree

**Q: What is the fundamental property that distinguishes a Binary Search Tree (BST) from a regular Binary Tree?** **A:** In a BST, for every node, all values in its **left subtree** must be smaller than the node's value, and all values in its **right subtree** must be larger. A regular Binary Tree has no such ordering rule.

### 2. Time Complexity (The "Big O")

**Q: What is the time complexity of searching for an element in a Balanced BST vs. a Skewed BST?** **A:** * **Balanced BST:** $O(\log n)$ because you eliminate half the tree with every step (similar to binary search).

- **Skewed BST (looks like a linked list):** $O(n)$ because you might have to visit every node.
    

### 3. Traversal Types

**Q: Name the three Depth-First Search (DFS) traversals and their orders.** 

1. **Pre-order:** Root $\rightarrow$ Left $\rightarrow$ Right (Useful for cloning trees).

2. **In-order:** Left $\rightarrow$ Root $\rightarrow$ Right (Produces sorted output in a BST).

3. **Post-order:** Left $\rightarrow$ Right $\rightarrow$ Root (Useful for deleting trees).

### 4. The "Sorted" Trick

**Q: If you perform an In-order traversal on a BST, what is unique about the resulting sequence?** **A:** The values will always be in **non-decreasing (sorted) order**. This is a common interview "trick" used to validate if a tree is a BST.

### 5. Height vs. Depth

**Q: What is the difference between the "height" of a node and the "depth" of a node?** 
**A:** 
**Depth:** The number of edges from the **root** to that node.

- **Height:** The number of edges on the longest path from that node to a **leaf**. (The height of the tree is the height of the root).
    

### 6. BFS vs. DFS

**Q: Which traversal method would you use to find the shortest path in a tree (or unweighted graph), and which data structure facilitates it?** **A:** **Breadth-First Search (BFS)**. It visits nodes level-by-level. It is implemented using a **Queue**.

### 7. Full, Complete, and Perfect Trees

**Q: What is a "Complete Binary Tree"?** **A:** A tree where every level is totally filled except possibly the last, and all nodes in the last level are as far left as possible. (This is why they map perfectly to arrays!)

### 8. Lowest Common Ancestor (LCA)

**Q: In a BST, how do you find the Lowest Common Ancestor of two nodes, $p$ and $q$?** **A:** You start at the root:

1. If both $p$ and $q$ are smaller than the root, move **left**.
    
2. If both $p$ and $q$ are larger than the root, move **right**.
    
3. If one is smaller and one is larger (or the root is one of them), the current root **is** the LCA.
    

### 9. Self-Balancing Trees

**Q: Why are self-balancing trees like AVL or Red-Black trees used in production databases?** **A:** They prevent the tree from becoming "skewed" (turning into $O(n)$). They ensure that the tree height stays $O(\log n)$ through "rotations" after every insertion or deletion, keeping operations consistently fast.

### 10. The "Successor" Problem

**Q: How do you find the "In-order Successor" of a node in a BST?** **A:** * If the node has a **right child**: The successor is the leftmost node in the right subtree.

- If the node has **no right child**: The successor is the lowest ancestor such that the node is in its left subtree.
    

---

### The Memory Palace: The Royal Family Tree

Imagine a **Kingdom** (The Tree).

- **The Root:** The King/Queen at the top.
    
- **BST Rule:** The "Left" branch of the family is always less wealthy than the parent, and the "Right" branch is always wealthier.
    
- **In-Order Traversal:** A tax collector walking through the kingdom from the poorest house to the wealthiest house in a straight line.
    
- **BFS:** A news crier shouting news. First, the King hears it, then all the King's children hear it, then all the grandchildren. They hear it "level by level."
    

![](https://encrypted-tbn0.gstatic.com/licensed-image?q=tbn:ANd9GcSVBUbMu9t8q9r5oL-dzk9xxUtb5bjcWznqHup7G48Jz8srJUpbOAAF2jL-J_tCAIoTuHCukFiztn1uCRSbim5R3vKIhkUgFnzMsbdqVVttNA5vyn0)

---

**Final Interview Advice:** When coding tree problems, **always** check for the `None` (Null) case first. If you forget `if root is None: return`, your code will likely crash during the recursion!

Would you like to try coding the **In-order Traversal** or the **LCA** algorithm?