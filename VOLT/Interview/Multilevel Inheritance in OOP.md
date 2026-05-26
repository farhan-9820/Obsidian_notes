**Multilevel Inheritance** is a mechanism where a class is derived from another derived class, creating a "grandparent-parent-child" chain. Unlike multiple inheritance (where one child has two parents), multilevel inheritance involves a single linear path of ancestry.

---

## 1. The Theory: The "Chain of Command"

In this model, features are passed down through the levels. Each subsequent child class inherits all the properties and methods of the classes above it in the hierarchy.

- **Relationship:** Class C inherits from Class B, and Class B inherits from Class A. Therefore, Class C transitively inherits from Class A.
    
- **Real-world Analogy:** * **Grandparent:** `Vehicle` (Basic movement)
    
    - **Parent:** `Car` (Adds wheels and doors)
        
    - **Child:** `ElectricCar` (Adds battery and charging)
        

---

## 2. Code Implementation

In this example, note how `Tesla` can access methods from both `Car` and `Vehicle`.

```python

class Vehicle:
    def move(self):
        print("Moving on the road...")

class Car(Vehicle):
    def fuel_type(self):
        print("Uses Gasoline/Electricity")

class Tesla(Car):
    def self_drive(self):
        print("Autopilot mode engaged!")

# Object of the derived-most class
my_tesla = Tesla()

my_tesla.move()        # Inherited from Grandparent (Vehicle)
my_tesla.fuel_type()   # Inherited from Parent (Car)
my_tesla.self_drive()  # Own method
```

---

## 3. Interview Focus: Method Overriding & `super()`

In a multilevel structure, an interview question might ask: _"If I call `super()` in the grandchild, which class's method is executed?"_

The answer is: **The immediate parent.** However, you can chain `super()` calls to reach the grandparent.


```python


class Grandparent:
    def display(self):
        print("Message from Grandparent")

class Parent(Grandparent):
    def display(self):
        print("Message from Parent")
        super().display()  # Calls Grandparent

class Child(Parent):
    def display(self):
        print("Message from Child")
        super().display()  # Calls Parent

c = Child()
c.display()
```

**Output:**

1. `Message from Child`
    
2. `Message from Parent`
    
3. `Message from Grandparent`
    

---

## 4. Key Considerations for Interviews

### Method Resolution Order (MRO)

In multilevel inheritance, the MRO is very simple because it's a straight line.

For the code above, the MRO would be: `[Child, Parent, Grandparent, object]`.

### Transitive Property

A common misconception is that a child only knows about its immediate parent. In reality, the child class has access to the **entire public and protected interface** of every class above it in the chain.

### Why use it?

- **Specialization:** You start with a general idea (`Animal`) and get more specific (`Mammal` -> `Primate` -> `Human`) at each level.
    
- **Organization:** It keeps the code clean by separating concerns (e.g., `Vehicle` handles movement, `Car` handles wheels, `Tesla` handles tech).
    

---

## 5. Comparison: Multiple vs. Multilevel

Interviewers love to compare these two:

|**Feature**|**Multiple Inheritance**|**Multilevel Inheritance**|
|---|---|---|
|**Structure**|One child, many parents.|One parent, one child (in a chain).|
|**Complexity**|High (Diamond Problem).|Low (Linear flow).|
|**Syntax**|`class C(A, B):`|`class B(A):` then `class C(B):`|

Would you like to finish the inheritance set by looking at **Hierarchical** or **Hybrid** inheritance, or shall we move on to how **Private variables** behave across these levels?