```python

def copy_list(source):
    # Line 2-3: Initialize the new list's head and tail
    copy_head = None
    copy_tail = None
    
    # Line 4: Start at the beginning of the source list
    temp = source
    
    # Line 5: Traverse the source list
    while temp is not None:
        # Line 6: Create a brand new node with the same data
        n = Node(temp.elem, None)
        
        # Line 7-9: If this is the first node being copied
        if copy_head is None:
            copy_head = n
            copy_tail = copy_head
        else:
            # Line 11-12: Link the new node to the end of the copy
            copy_tail.next = n
            copy_tail = copy_tail.next
            
        # Line 14: Move to the next node in the source
        temp = temp.next
        
    # Line 16: Return the head of the new, independent list
    return copy_head
```


