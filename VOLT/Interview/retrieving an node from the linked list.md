```python

def nodeAt(head, idx):
    # Line 2-3: Initialize counter and starting point
    count = 0
    temp = head
    
    # Line 4: Traverse the list
    while temp is not None:
        # Line 5-7: If we found the right index, return the NODE itself
        if count == idx:
            return temp
        
        # Line 8-9: Advance to the next node
        temp = temp.next
        count += 1
        
    # Line 11: Return None if index is out of range
    return None
```

