```python

class Node:
    def __init__(self, value):
        self.value = value
        self.left = None
        self.right = None

def build_tree_array(root, tree_array, index):
    # Line 3: If the root is not NULL
    if root is not None:
        # Set the root node value at the given index
        tree_array[index] = root.value
        
        # Line 4a: Left child is at index 2*i
        if root.left:
            build_tree_array(root.left, tree_array, 2 * index)
            
        # Line 4b: Right child is at index 2*i + 1
        if root.right:
            build_tree_array(root.right, tree_array, 2 * index + 1)

# Usage Example:
# Let's assume a max size of 10 for the array
n = 10
tree_array = [None] * (n + 1)

# Creating a small tree:
#      A(1)
#     /    \
#   B(2)   C(3)
root = Node("A")
root.left = Node("B")
root.right = Node("C")

build_tree_array(root, tree_array, 1)
print(tree_array) 
# Output: [None, 'A', 'B', 'C', None, None, None, None, None, None, None]
```