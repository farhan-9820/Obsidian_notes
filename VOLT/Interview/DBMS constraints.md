In database management, **constraints** are the rules enforced on data columns to ensure the accuracy, reliability, and integrity of the information within the database. If an action violates a constraint, the database engine will abort it.

---

## 1. Domain Constraint

This is the most fundamental level of constraint. It defines the **valid values** for a specific column.

- **Definition:** It restricts the "domain" (data type, format, or range) of an attribute.
    
- **Specialty:** It ensures that if a column is meant for "Age," someone can't enter "Banana" or a negative number.
    
- **Examples:** Data types (INTEGER, VARCHAR), `CHECK` constraints (e.g., `Age >= 18`), or `NOT NULL`.
    

## 2. Key Constraint

Key constraints ensure that an entity (row) can be uniquely identified and that specific attributes remain distinct.

- **Definition:** It requires that the values in a specific attribute (like a Primary Key) are **unique** across the entire table.
    
- **Specialty:** It prevents duplicate records. Even if two people have the same name, a Key Constraint on "Student_ID" ensures they are treated as two distinct individuals.
    

## 3. Entity Integrity Constraint

This rule specifically governs the behavior of **Primary Keys**.

- **The Rule:** The Primary Key of a table **cannot be NULL**.
    
- **Specialty:** Every row _must_ have a unique identity to be accessible. If a Primary Key were null, we would have no reliable way to identify or link that specific row.
    
- **Difference from Key Constraint:** While a unique key constraint might allow one null value, Entity Integrity strictly forbids any nulls in the primary identifier.
    

## 4. Referential Integrity Constraint (RIC)

This rule governs the relationship **between** tables using Foreign Keys.

- **The Rule:** A Foreign Key value in Table A must either:
    
    1. Match a Primary Key value in Table B.
        
    2. Or be completely NULL (if the relationship is optional).
        
- **Specialty:** It prevents "orphaned" records. For example, it ensures you cannot assign a student to a `Department_ID` that doesn't actually exist in the Departments table.
    
- **Common Actions:** RIC often involves `ON DELETE CASCADE` (deleting a parent deletes the child) or `ON DELETE SET NULL`.
    

---

### Summary Comparison Table

|**Constraint**|**Scope**|**Primary Goal**|
|---|---|---|
|**Domain**|Column / Attribute|Validates format, type, and range.|
|**Key**|Table / Rows|Ensures uniqueness of records.|
|**Entity Integrity**|Primary Key|Guarantees every row has a non-null ID.|
|**Referential Integrity**|Between Tables|Maintains consistent links between related data.|

Are you currently designing a schema where you're deciding between `CASCADE` or `RESTRICT` for your referential integrity?