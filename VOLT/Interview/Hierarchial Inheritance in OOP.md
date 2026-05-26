**Hierarchical Inheritance** occurs when **multiple child classes inherit from a single parent class**.

While Multilevel inheritance is a "chain," Hierarchical inheritance is a "tree." It allows you to define common logic in one base class and then branch out into specialized versions of that logic.

---

## 1. The Theory: One Source, Many Variations

This is the most common form of inheritance in software development because it follows the principle of **DRY (Don't Repeat Yourself)**. If several classes share the same basic attributes, you pull those attributes "up" into a single parent class.

- **Relationship:** Class B _is-a_ Class A, and Class C _is-a_ Class A.
    
- **Real-world Analogy:** * **Parent:** `Bank Account` (Has account number, balance)
    
    - **Child 1:** `Savings Account` (Adds interest rate)
        
    - **Child 2:** `Current Account` (Adds overdraft limit)
        

---

## 2. Code Implementation

In this scenario, `Developer` and `Manager` both need an `id` and `name`, but they have different work duties.

```python


class Employee:
    def __init__(self, name, emp_id):
        self.name = name
        self.emp_id = emp_id

    def show_details(self):
        print(f"ID: {self.emp_id} | Name: {self.name}")

# Child 1
class Developer(Employee):
    def work(self):
        print(f"{self.name} is writing code.")

# Child 2
class Manager(Employee):
    def work(self):
        print(f"{self.name} is managing the team.")

# Usage
dev = Developer("Eve", 101)
mgr = Manager("Adam", 102)

dev.show_details()  # Accessing Parent method
dev.work()          # Accessing own method

mgr.show_details()  # Accessing Parent method
mgr.work()          # Accessing own method
```

---

## 3. Interview-Specific Concepts

### The Benefit of Polymorphism

Hierarchical inheritance is the perfect setup for **Polymorphism**. Since both `Developer` and `Manager` are types of `Employee`, you can process them in a single loop even though their `work()` behaviors differ.

Python

```python

employees = [Developer("Eve", 101), Manager("Adam", 102)]

for emp in employees:
    emp.work() # Python knows which work() method to call for each object
```

### Namespace Isolation

In an interview, you might be asked: _"Does the `Developer` class have access to the `Manager` class's methods?"_

**The answer is No.** Even though they share the same parent, they are siblings. Their namespaces are completely isolated from each other.

---

## 4. Key Advantages & Use Cases

- **Centralized Control:** If you want to change how all employees are identified (e.g., adding a "Department" attribute), you only change the `Employee` class.
    
- **Logical Grouping:** It mirrors real-life taxonomies, making the codebase intuitive for other developers to read.
    
- **Scalability:** You can easily add a third child class, like `Designer`, without affecting the existing `Developer` or `Manager` code.
    

---

## 5. Comparison: Hierarchical vs. Multiple

|**Feature**|**Hierarchical**|**Multiple**|
|---|---|---|
|**Parent/Child Ratio**|1 Parent : Many Children|Many Parents : 1 Child|
|**Logic Sharing**|Children share Parent's logic.|Child combines Parents' logics.|
|**Conflict Risk**|Low (Each branch is separate).|High (Potential naming conflicts).|

We have now covered Single, Multiple, Multilevel, and Hierarchical. The final (and most complex) type is **Hybrid Inheritance**. Would you like to tackle that, or shall we discuss the **"Diamond Problem"** in more technical depth?