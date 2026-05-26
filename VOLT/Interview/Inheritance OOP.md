# 1. Core Concepts & Syntax

At its simplest, inheritance is about "is-a" relationships. For example, a `Developer` **is-a** `Employee`.

### The Basic Syntax


```python 

class Parent:
    def __init__(self, name):
        self.name = name

    def greet(self):
        print(f"Hello, I am {self.name}")

class Child(Parent):  # Inheriting from Parent
    pass

c = Child("Alice")
c.greet()  # Output: Hello, I am Alice
```

# 2. Types of Inheritance 

- [[Single Inheritance in OOP]]

- [[Multiple inheritance in oop]]

- [[Multilevel Inheritance in OOP]]

- [[Hierarchial Inheritance in OOP]]

- [[Hybrid Inheritance in OOP]]


# 3. The `super()` Function and `__init__`

A common interview question is: _"How do you call the parent constructor?"_

If you define an `__init__` method in the child class, it **overrides** the parent's `__init__`. To ensure the parent is properly initialized, use `super()`.

```python

class Animal:
    def __init__(self, species):
        self.species = species

class Dog(Animal):
    def __init__(self, breed, species):
        # Call the parent constructor
        super().__init__(species)
        self.breed = breed

d = Dog("Golden Retriever", "Canine")
print(d.species) # Output: Canine
```


# 4. Method Resolution Order (MRO)

[[Method Resolution Order in Inheritance (oop)]]


# 5. Method Overriding 

[[Method Overriding in oop]]



# 6. Interview "Gotchas" to Remember

- **Object Class:** In Python 3, every class implicitly inherits from the built-in `object` class.
    
- **Private Members:** Members prefixed with `__` (double underscore) are "mangled" and not easily accessible by the child class. This is called **Name Mangling**.
    
- **isinstance() vs issubclass():**
    
    - `isinstance(obj, Class)`: Checks if an object is an instance of a class or a subclass thereof.
        
    - `issubclass(Child, Parent)`: Checks if a class is derived from another class.
        

---

# 7. Abstract Base Classes (ABC)

Sometimes you want to ensure that a child class **must** implement certain methods. You use the `abc` module for this.


```python


from abc import ABC, abstractmethod

class Shape(ABC):
    @abstractmethod
    def area(self):
        pass

class Square(Shape):
    def __init__(self, side):
        self.side = side
    
    def area(self):
        return self.side * self.side

# s = Shape()  # This would raise an error!
```

