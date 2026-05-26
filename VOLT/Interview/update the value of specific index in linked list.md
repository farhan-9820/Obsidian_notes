```python

def set_elem(head, idx, elem):
    # Line 2-4: Setup variables
    count = 0
    temp = head
    is_updated = False
    
    # Line 5: Traverse the list
    while temp is not None:
        # Line 6-10: If index is found, update data and exit loop
        if count == idx:
            temp.elem = elem
            is_updated = True
            break
        
        # Line 11-12: Move to next node
        temp = temp.next
        count += 1
        
    # Line 14-18: Status reporting
    if is_updated:
        print("Value successfully updated!!!!")
    else:
        print("Invalid index")
```

