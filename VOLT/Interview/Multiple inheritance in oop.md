**Multiple Inheritance** is a feature where a class can inherit attributes and methods from **more than one parent class**. While powerful, it is significantly more complex than single inheritance because it introduces the possibility of ambiguity—especially when multiple parents have methods with the same name.

---

## 1. The Theory: Combining Behaviors
In multiple inheritance, the child class represents a combination of different "traits" or "functionalities." It is often used to implement **Mixins**, which are small classes designed to provide specific sets of features to other classes.

* **Example:** A `Smartphone` class might inherit from a `Camera` class and a `Phone` class.



---

## 2. Basic Syntax and Code
The parent classes are listed inside the parentheses, separated by commas.

```python
class Camera:
    def take_photo(self):
        print("Photo taken!")

class Phone:
    def make_call(self):
        print("Calling...")

# Multiple Inheritance: Smartphone inherits from BOTH Camera and Phone
class Smartphone(Camera, Phone):
    def browse_internet(self):
        print("Browsing the web")

iphone = Smartphone()
iphone.take_photo()  # From Camera
iphone.make_call()   # From Phone
iphone.browse_internet() # Own method
```

---

## 3. The Interview "Must-Know": The Diamond Problem
The biggest challenge with multiple inheritance is the **Diamond Problem**. This occurs when two parent classes inherit from the same grandparent, and the child class inherits from both parents.



If both `B` and `C` override a method from `A`, which one does `D` use? 

### [[Method Resolution Order in Inheritance (oop)]] 
Python solves this using the **C3 Linearization algorithm**. It creates a linear list of classes to search when a method is called. You can check this order using `ClassName.mro()`.

```python
class A:
    def greet(self):
        print("Hello from A")

class B(A):
    def greet(self):
        print("Hello from B")

class C(A):
    def greet(self):
        print("Hello from C")

class D(B, C):
    pass

obj = D()
obj.greet()  # Output: Hello from B

# To see why:
print(D.mro())
# Output: [<class 'D'>, <class 'B'>, <class 'C'>, <class 'A'>, <class 'object'>]
```

**Key Interview Point:** Python follows a **"Depth-First, Left-to-Right"** approach but ensures that a shared base class (like `A`) is only visited *after* all its derived classes (like `B` and `C`) have been searched.

---

## 4. `super()` in Multiple Inheritance
In multiple inheritance, `super()` does **not** necessarily call the "parent." It calls the **next class in the MRO**.

```python
class Base:
    def __init__(self):
        print("Base init")

class Child1(Base):
    def __init__(self):
        print("Child1 init")
        super().__init__()

class Child2(Base):
    def __init__(self):
        print("Child2 init")
        super().__init__()

class GrandChild(Child1, Child2):
    def __init__(self):
        print("GrandChild init")
        super().__init__()

gc = GrandChild()
```
**Output Order:** 1. `GrandChild init`
2. `Child1 init`
3. `Child2 init` (This surprises people! `super()` in `Child1` jumps to `Child2` based on the MRO)
4. `Base init`

---

## 5. Summary for Interviews

* **Complexity:** Multiple inheritance increases the complexity of the code and can make debugging difficult.
* **MRO:** Always mention the **C3 Linearization algorithm** and the `.mro()` method.
* **The Diamond Problem:** Be ready to explain how Python avoids ambiguity by ordering the search path.
* **Best Practice:** In modern software design, many developers prefer **Composition over Inheritance** or using **Mixins** to avoid the pitfalls of deep multiple inheritance hierarchies.

Since we've covered Single and Multiple, would you like to dive into **Multilevel Inheritance**, or are you curious about how **Abstract Base Classes** tie into all of this?