```python

class Node:
    def __init__(self, e, n):
        self.elem = e
        self.next = n

def create_list(arr):
    if not arr:
        return None
    
    # Line 2: Create the head node
    head = Node(arr[0], None)
    
    # Line 3: Initialize the tail to track the end of the list
    tail = head
    
    # Line 4-8: Iterate through the rest of the array
    for i in range(1, len(arr)):
        # Line 5: Create a new node for the current element
        n = Node(arr[i], None)
        
        # Line 6: Link the current tail to the new node
        tail.next = n
        
        # Line 7: Move the tail pointer to the new node
        tail = tail.next
        
    # Line 9: Return the starting point of the list
    return head
```


