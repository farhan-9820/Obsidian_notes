## 1. The Theory: Flexibility in Action

Polymorphism allows you to define methods in a child class with the same name as methods in the parent class, but with different logic. It also allows functions to take different types of objects as arguments and still perform the correct operation.

## 2. Types of Polymorphism in Python

Unlike languages like Java or C++, Python handles polymorphism very dynamically. There are three main ways it manifests:

### A. Duck Typing

This is a core Python philosophy: _"If it walks like a duck and quacks like a duck, then it must be a duck."_ Python doesn't care about the **type** of the object; it only cares if the object has the **method** you are trying to call.


```python


class Duck:
    def swim(self): print("Swimming like a duck")

class Human:
    def swim(self): print("Swimming like a human")

def test_swim(obj):
    # This function doesn't care if obj is a Duck or Human
    obj.swim()

test_swim(Duck())  # Works
test_swim(Human()) # Works
```

### B. Method Overriding (Run-time Polymorphism)

This occurs when a child class changes the implementation of a method inherited from a parent. The version of the method that gets called is determined at **run-time** based on the object type.


```python

class Bird:
    def fly(self):
        print("Most birds can fly.")

class Sparrow(Bird):
    def fly(self):
        print("Sparrows fly high.")

class Penguin(Bird):
    def fly(self):
        print("Penguins cannot fly, they swim.")

birds = [Sparrow(), Penguin()]
for b in birds:
    b.fly() 
```

### C. Operator Overloading

The same operator behaves differently depending on the operands. For example, the `+` operator adds numbers but concatenates strings. You can define this behavior for your own classes using "Magic Methods" (Dunder methods).


```python

print(5 + 5)          # Output: 10 (Addition)
print("Py" + "thon")  # Output: Python (Concatenation)

class Vector:
    def __init__(self, x, y):
        self.x = x
        self.y = y
    
    def __add__(self, other):
        return Vector(self.x + other.x, self.y + other.y)

v1 = Vector(1, 2)
v2 = Vector(3, 4)
v3 = v1 + v2 # Uses the __add__ magic method
```

---

## 3. Interview "Gotcha": Does Python support Method Overloading?

**Technically, No.** In languages like Java, you can have multiple methods with the same name but different parameters (e.g., `add(int a, int b)` and `add(int a, int b, int c)`).

In Python, if you define a method twice, the **latest definition** replaces the previous one. However, we _simulate_ overloading using **default arguments** or **variable-length arguments (`*args`, `**kwargs`)**.


```python

class Calculator:
    def add(self, a, b, c=0):  # 'c' is optional
        return a + b + c

calc = Calculator()
print(calc.add(2, 3))    # Works like 2-param method
print(calc.add(2, 3, 5)) # Works like 3-param method
```

---

## 4. Key Benefits for Developers

1. **Extensibility:** You can add new classes (e.g., a `Whale` class) without changing the existing functions that process them (e.g., `test_swim`).
    
2. **Clean Code:** It reduces the need for complex `if-else` or `switch` statements to check for object types.
    
3. **Interface Consistency:** It ensures that different objects provide a consistent "look and feel" to the user of the class.
    

---

## 5. Summary Table for Interviews

|**Concept**|**Description**|
|---|---|
|**Method Overriding**|Child class provides a specific implementation of a parent method.|
|**Method Overloading**|Multiple methods with the same name but different parameters (Simulated in Python).|
|**Operator Overloading**|Changing the behavior of operators (+, -, *, etc.) for custom classes.|
|**Duck Typing**|The type of the object is less important than the methods it defines.|