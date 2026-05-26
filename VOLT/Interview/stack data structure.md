# Three basic operations 

> last in first out (LIFO)

- push ()
- pop ()
- peek ()


```python

class Stack:
    def __init__(self):
        self.stack = []  # Our container

    def is_empty(self):
        return len(self.stack) == 0
```

```python

def push(self, item):
        self.stack.append(item)
        print(f"Pushed: {item}")
```

```python

def peek(self):
        if self.is_empty():
            return "Stack is empty!"
        return self.stack[-1]
```


# questions 

[[stack data structure questions]]