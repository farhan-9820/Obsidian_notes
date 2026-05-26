
---

### Conceptual Questions

**1. What is the difference between `DELETE`, `TRUNCATE`, and `DROP`?**

- **DELETE:** A DML command that removes specific rows (can be rolled back).
    
- **TRUNCATE:** A DDL command that removes all rows from a table (faster, resets auto-increment).
    
- **DROP:** Removes the entire table structure and data from the database.
    

**2. What are the common types of Joins in MySQL?**

Be ready to explain **INNER JOIN**, **LEFT JOIN**, **RIGHT JOIN**, and **CROSS JOIN**. Mention that MySQL does not have a built-in `FULL OUTER JOIN`, but you can emulate it using `UNION`.

**3. Explain the difference between `WHERE` and `HAVING`.**

- `WHERE` filters rows **before** any groupings are made.
    
- `HAVING` filters groups **after** the `GROUP BY` clause has been applied.
    

**4. What is an Index, and why do we use it?**

An index is a data structure (usually a B-Tree in MySQL) that allows the server to find rows faster. Explain the trade-off: it speeds up `SELECT` queries but slows down `INSERT` and `UPDATE` operations because the index must also be updated.

**5. What is the difference between `Primary Key` and `Unique Key`?**

A Primary Key cannot be NULL and there is only one per table. A Unique Key allows one NULL value (in MySQL) and you can have multiple Unique columns in a single table.

---

### Practical & Query Questions

**6. How do you find the second highest salary from an "Employees" table?**

This is a classic. You can use `LIMIT` and `OFFSET`:

SQL

```
SELECT Salary FROM Employees 
ORDER BY Salary DESC 
LIMIT 1 OFFSET 1;
```

**7. Write a query to find duplicate records in a table.**

You’ll need to group by the column that has duplicates and check the count:

SQL

```
SELECT Email, COUNT(Email) 
FROM Users 
GROUP BY Email 
HAVING COUNT(Email) > 1;
```

**8. What is the purpose of the `UNION` operator?**

It combines the result sets of two or more `SELECT` statements into a single result set. Note that `UNION` removes duplicates, while `UNION ALL` keeps them.

**9. How do you select rows where a name starts with the letter 'A'?**

Use the `LIKE` operator with a wildcard:

SQL

```
SELECT * FROM Students WHERE Name LIKE 'A%';
```

**10. What are ACID properties in a database?**

As a CS student, this is a must-know. Briefly define **Atomicity**, **Consistency**, **Isolation**, and **Durability**. Mention that engines like **InnoDB** support ACID, while **MyISAM** does not.

---

### Pro-Tips for the Interview:

- **Normalization:** Be ready to briefly explain 1NF, 2NF, and 3NF if they ask about database design.
    
- **Handwriting Code:** Sometimes interns are asked to write queries on a whiteboard or a shared doc. Practice writing your `JOIN` syntax clearly.
    
- **Aggregates:** Make sure you're comfortable with `SUM()`, `AVG()`, `COUNT()`, `MIN()`, and `MAX()`.
    




---
---

Answers
---
## 1. DELETE vs. TRUNCATE vs. DROP

- **DELETE:** Logged per row. You can use a `WHERE` clause. It is a **DML** (Data Manipulation Language) command.
    
- **TRUNCATE:** Deletes all rows by deallocating the data pages. It’s faster and is a **DDL** (Data Definition Language) command. It resets the `AUTO_INCREMENT` counter.
    
- **DROP:** Deletes the table definition and all data. The table ceases to exist.
    

## 2. Common Joins

- **Inner Join:** Returns records with matching values in both tables.
    
- **Left Join:** Returns all records from the left table and matched records from the right.
    
- **Right Join:** Returns all records from the right table and matched records from the left.
    
- **Cross Join:** Returns the Cartesian product (every row from A paired with every row from B).
    

## 3. WHERE vs. HAVING

- **WHERE:** Filters individual rows **before** aggregation. You cannot use aggregate functions (like `SUM` or `COUNT`) here.
    
- **HAVING:** Filters groups **after** the `GROUP BY` clause.
    

## 4. Understanding Indexes

- **Answer:** An index is a structure that improves data retrieval speed at the cost of storage space and slower writes.
    
- **Specialty:** Mention **B-Tree** indexes. They keep data sorted and allow for binary-style searches ($O(\log n)$) instead of linear scans ($O(n)$).
    

## 5. Primary Key vs. Unique Key

- **Primary Key:** Unique, Not Null, only **one** per table. It defines the physical storage order in InnoDB (Clustered Index).
    
- **Unique Key:** Unique, allows **one** NULL, you can have **multiple** per table.
    

## 6. Second Highest Salary Query

SQL

```
SELECT DISTINCT Salary 
FROM Employees 
ORDER BY Salary DESC 
LIMIT 1 OFFSET 1;
```

- _Note:_ Using `DISTINCT` is safer in case two people share the top salary.
    

## 7. Finding Duplicate Records

SQL

```
SELECT column_name, COUNT(*)
FROM table_name
GROUP BY column_name
HAVING COUNT(*) > 1;
```

## 8. UNION vs. UNION ALL

- **UNION:** Combines results and performs a distinct operation to remove duplicates (slower).
    
- **UNION ALL:** Combines results but keeps duplicates (faster).
    

## 9. Pattern Matching (LIKE)

- **`'A%'`**: Starts with A.
    
- **`'%A'`**: Ends with A.
    
- **`'%A%'`**: Contains A in any position.
    
- **`'_A%'`**: 'A' is in the second position.
    

## 10. ACID Properties

- **Atomicity:** "All or nothing." The transaction fully completes or fully fails.
    
- **Consistency:** The database moves from one valid state to another.
    
- **Isolation:** Transactions don't interfere with each other.
    
- **Durability:** Once committed, data survives system failures.
    

---

### Comparison of Statement Types

|**Command**|**Category**|**Rollback Possible?**|
|---|---|---|
|**SELECT**|DQL|N/A|
|**INSERT/UPDATE/DELETE**|DML|Yes|
|**CREATE/DROP/TRUNCATE**|DDL|No (Auto-commits in MySQL)|
|**GRANT/REVOKE**|DCL|No|

Would you like me to explain how any of these specifically relate to the **MERN stack** projects you've been working on?