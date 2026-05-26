This is the "pro level" interview topic. In multiple inheritance, if two parents have the same method, which one does Python call?

Python uses the **C3 Linearization algorithm** to determine the MRO. You can inspect it using the `.mro()` method or the `__mro__` attribute.

### The Diamond Problem Example


```python

class A:
    def speak(self): print("A")

class B(A):
    def speak(self): print("B")

class C(A):
    def speak(self): print("C")

class D(B, C):
    pass

obj = D()
obj.speak() 
print(D.mro())
```

**Output:**

- `B` (Because `B` comes before `C` in the class definition `class D(B, C)`)
    
- MRO: `[D, B, C, A, object]`

