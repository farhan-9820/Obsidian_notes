```python

def elem_at(head, idx):
    # Line 2-3: Initialize counter and starting point
    count = 0
    temp = head
    
    # Line 4: Traverse until the end of the list
    while temp is not None:
        # Line 5-7: Check if the current position matches the target index
        if count == idx:
            return temp.elem
        
        # Line 8-9: Move to next node and increment counter
        temp = temp.next
        count += 1
        
    # Line 11: If we exit the loop, the index was out of bounds
    return None
```

