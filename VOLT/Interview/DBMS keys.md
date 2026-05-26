In database management systems (DBMS), **keys** are the attributes (columns) that establish relationships between tables and ensure that data remains unique and organized. Think of them as the DNA of a database record.

---

## 1. Super Key

A **Super Key** is the most basic set of one or more columns that can uniquely identify a row in a table. It is the "broadest" category.

- **Specialty:** It is any combination of columns that ensures no two rows are identical.
    
- **Example:** In a "Student" table, `(ID)`, `(ID, Name)`, and `(Email, Phone)` are all super keys because they all contain enough information to distinguish one student from another.
    

## 2. Candidate Key

A **Candidate Key** is a "minimal" super key. It is a super key that contains no unnecessary extra columns.

- **Specialty:** Every candidate key has the potential to become the primary key. It must contain unique values and cannot be null.
    
- **The Difference:** If `(ID, Name)` is a super key, it is **not** a candidate key because `(ID)` alone is enough to identify the row; the `Name` is redundant.
    

## 3. Primary Key

The **Primary Key** is the specific candidate key chosen by the database designer to uniquely identify records throughout the table.

- **Specialty:** There can be **only one** primary key per table. It strictly forbids `NULL` values and must be unique.
    
- **Example:** Between `(ID)` and `(Email)`, the designer chooses `ID` as the Primary Key.
    

## 4. Foreign Key

A **Foreign Key** is a column in one table that points to the **Primary Key** in another table.

- **Specialty:** Its main job is **Referential Integrity**—it links two tables together.
    
- **The Difference:** While other keys focus on uniqueness _within_ a table, the foreign key focuses on the relationship _between_ tables. It can contain duplicate values or nulls (unless specified otherwise).
    

---

### Comparison Table: Key Differences

|**Feature**|**Super Key**|**Candidate Key**|**Primary Key**|**Foreign Key**|
|---|---|---|---|---|
|**Uniqueness**|Must be unique|Must be unique|Must be unique|Can be duplicate|
|**Null Values**|Can allow nulls|Usually no nulls|**Never** allows nulls|Can allow nulls|
|**Quantity**|Many possible|Many possible|**Only One**|Many possible|
|**Purpose**|Identify rows|Potential PK|Main Identifier|Link Tables|

---

### The "Specialty" Breakdown

- **Super Key** is the **All-inclusive** group.
    
- **Candidate Key** is the **Elite** group (no fluff).
    
- **Primary Key** is the **Chosen** leader.
    
- **Foreign Key** is the **Bridge** to other tables.
    

Which of these keys are you planning to implement in your current project?