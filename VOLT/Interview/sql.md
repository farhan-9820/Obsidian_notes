how to create a database ? 
- CREATE DATABASE database_name

how to delete/drop database? 
DROP DATABASE databse_name

how to use the created database? 
- USE database_name

how to create table inside the database? (including the columns)
``` mysql
CREATE TABLE users (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    email VARCHAR(255) UNIQUE,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

```

how to alter table? (say adding another column) --> also tell about varchar? 
```mysql
ALTER TABLE table_name
ADD column_name datatype;

ALTER TABLE Employees
ADD email VARCHAR(255);
```


how to define a foreign key in sql?  along with REFERENCES
```mysql
CREATE TABLE Orders (
    OrderID int PRIMARY KEY,
    CustomerID int,
    FOREIGN KEY (CustomerID) REFERENCES Customers(CustomerID)
);
```

how to insert values in database? along with advanced insertion , how to input multiple inputs (for multiple columns )
`INSERT INTO Students (Name, Age) VALUES ('John Doe', 20)`

how to query from the database? limit, also discuss about distinct 
`SELECT column_name FROM table_name LIMIT number;`

how to rename the columns? (like aliasing)

```mysql
SELECT column_name AS alias_name
FROM table_name;
```

---

order by 

how to reverse order? 

```mysql 
SELECT column_name(s)
FROM table_name
ORDER BY column_name DESC;
```

---
how to update table? how to do this for every record and for single record? 
```mysql
UPDATE table_name 
SET column1 = 'new_value' 
WHERE id = 1;
```

---
filtering --> where 

LIKE  '%er%';

```mysql
-- Find products containing 'er' in the name
SELECT * FROM products WHERE product_name LIKE '%er%';

-- Find users with 'er' in their last name
SELECT * FROM users WHERE last_name LIKE '%er%';
```

---
BETWEEN 

`SELECT * FROM products WHERE price BETWEEN 10 AND 50;`

`SELECT * FROM customers WHERE last_name BETWEEN 'A' AND 'M';`

`SELECT * FROM orders WHERE order_date BETWEEN '2024-01-01' AND '2024-01-31';`

---
IS NULL 

```mysql
SELECT * FROM employees WHERE phone_number IS NULL;

SELECT * FROM contacts WHERE email IS NOT NULL;
```

---
DELETE FROM {table_name}

---
JOIN  (how to join tables)

INNER JOIN  

```mysql

SELECT t1.col, t2.col, t3.col
FROM table1 t1
JOIN table2 t2 ON t1.id = t2.t1_id
JOIN table3 t3 ON t2.id = t3.t2_id;
```

LEFT JOIN 

RIGHT JOIN 

---
aggregate function  

---
GROUP BY 

HAVING
```mysql 
SELECT Country, COUNT(CustomerID)
FROM Customers
GROUP BY Country
HAVING COUNT(CustomerID) > 5;
```

---
# nested queries --> 


- This example finds each employee and calculates how much more (or less) they earn compared to the **average salary of their specific department**.

```mysql 
SELECT 
    emp_name, 
    salary, 
    dept_id,
    (SELECT AVG(salary) 
     FROM employees e2 
     WHERE e2.dept_id = e1.dept_id) AS dept_avg_salary
FROM employees e1
WHERE salary > (
    SELECT AVG(salary) 
    FROM employees e3 
    WHERE e3.dept_id = e1.dept_id
);
```


- ### Nested Subquery with `NOT EXISTS`

This is used to find "orphaned" data. For example, finding customers who have **never placed an order for a specific category of product**.

```mysql
SELECT customer_name 
FROM customers c
WHERE NOT EXISTS (
    SELECT 1 
    FROM orders o
    JOIN order_details od ON o.order_id = od.order_id
    JOIN products p ON od.product_id = p.product_id
    WHERE o.customer_id = c.customer_id 
    AND p.category = 'Electronics'
);
```


- ### Derived Table (Subquery in `FROM`)

This query identifies the "Big Spenders"—customers whose total order value is higher than the average total order value of all customers.

```mysql

SELECT customer_id, total_spent
FROM (
    SELECT customer_id, SUM(order_total) AS total_spent
    FROM orders
    GROUP BY customer_id
) AS customer_totals
WHERE total_spent > (
    SELECT AVG(total_spent) 
    FROM (
        SELECT SUM(order_total) AS total_spent
        FROM orders
        GROUP BY customer_id
    ) AS inner_totals
);
```

