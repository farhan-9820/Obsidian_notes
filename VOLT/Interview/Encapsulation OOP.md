**Encapsulation** is the process of wrapping data (variables) and the methods that operate on that data into a single unit (a class). Think of it as a **protective shield** that prevents the data from being accessed or modified directly by code outside that shield.

In an interview, you should describe it as the mechanism for **data hiding**.

---

## 1. The Theory: Why Encapsulate?

The primary goal is to restrict direct access to certain components of an object, which is vital for:

- **Security:** Preventing accidental data corruption.
    
- **Integrity:** Ensuring that data can only be changed in "allowed" ways (e.g., a `balance` cannot be negative).
    
- **Flexibility:** You can change the internal implementation without affecting the code that uses the class.

## 2. Access Modifiers in Python

Unlike Java or C++, Python does not have strict `public`, `private`, or `protected` keywords. Instead, it uses **naming conventions** to indicate the intended level of access.

|**Name**|**Convention**|**Description**|
|---|---|---|
|**Public**|`name`|Accessible from anywhere (inside or outside the class).|
|**Protected**|`_name`|A hint that it's for internal use or subclasses (not enforced by Python).|
|**Private**|`__name__`|Strongly hidden from outside access via **Name Mangling**.|

---

## 3. Practical Code Example

Here is how you implement encapsulation and use **Getters** and **Setters** to manage access.


```python

class BankAccount:
    def __init__(self, owner, balance):
        self.owner = owner          # Public attribute
        self._account_type = "Gold" # Protected attribute
        self.__balance = balance    # Private attribute

    # Getter method: To view private data
    def get_balance(self):
        return self.__balance

    # Setter method: To modify private data with logic
    def deposit(self, amount):
        if amount > 0:
            self.__balance += amount
            print(f"Deposited {amount}. New balance: {self.__balance}")
        else:
            print("Invalid deposit amount!")

# Usage
account = BankAccount("John", 1000)

print(account.owner)        # Works (Public)
print(account._account_type) # Works, but discouraged (Protected)
# print(account.__balance)  # Raises AttributeError (Private)

print(account.get_balance()) # Success via Getter
account.deposit(500)         # Success via Setter
```

---

## 4. The Interview "Deep Dive": Name Mangling

If an interviewer asks, _"Is it truly impossible to access a private variable in Python?"_, the answer is **No**.

Python performs **Name Mangling** on double-underscore attributes. It internally renames `__balance` to `_ClassName__variableName`.

Python

```python

# Hacking into a private variable (Don't do this in real production!)
print(account._BankAccount__balance) # Output: 1500
```

**Your Interview Answer:** _"Python doesn't have true privacy. It uses name mangling to protect the developer from accidentally overriding or accessing data, but it trusts the programmer to be 'consenting adults' and respect the conventions."_

---

## 5. Using the `@property` Decorator

In modern Python, we often use the `@property` decorator to make getters and setters look like regular attribute access. This is considered more "Pythonic."

```python

class Person:
    def __init__(self, age):
        self.__age = age

    @property
    def age(self):
        return self.__age

    @age.setter
    def age(self, value):
        if value < 0:
            raise ValueError("Age cannot be negative!")
        self.__age = value

p = Person(25)
p.age = 30  # Calls the setter
print(p.age) # Calls the getter
```

---

## 6. Summary for Interviews

- **Encapsulation** is about bundling data and methods.
    
- **Data Hiding** is achieved using `_` (hint) and `__` (mangling).
    
- **Getters/Setters** (or `@property`) provide a controlled interface for data interaction.
    
- **Benefit:** It decouples the internal representation of an object from its public interface.