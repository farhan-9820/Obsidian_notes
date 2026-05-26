```python
def count(head):
    total = 0
    temp = head
    while temp:
        total += 1
        temp = temp.next
    return total
```

```python

def insert(head, elem, idx):
    total_nodes = count(head)
    
    # Line 3-5: Inserting at the very beginning
    if idx == 0:
        # Create new node pointing to the current head
        n = Node(elem, head)
        head = n
        
    # Line 6-11: Inserting in the middle
    elif 1 <= idx < total_nodes:
        n = Node(elem, None) # Create the new node
        n1 = nodeAt(head, idx - 1) # Node before the insertion point
        n2 = nodeAt(head, idx)     # Node currently at the insertion point
        
        n.next = n2  # New node points to the next one
        n1.next = n  # Previous node points to our new node
        
    # Line 12-15: Inserting at the very end
    elif idx == total_nodes:
        n = Node(elem, None)
        n1 = nodeAt(head, total_nodes - 1)
        n1.next = n
        
    # Line 16-17: Error handling
    else:
        print("Invalid Index")
        
    # Line 19: Return the (potentially new) head
    return head
```

