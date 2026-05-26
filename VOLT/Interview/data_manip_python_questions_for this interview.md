
## Answers: 10 Technical Scenarios (SQL & Pandas)

**1. The Duplicate Dilemma**

- **SQL:** Use `GROUP BY` on all columns and `HAVING COUNT(*) > 1` to find them. To remove them, use a Common Table Expression (CTE) with `ROW_NUMBER()`.
    
- **Pandas:** Use `df.duplicated()` to identify and `df.drop_duplicates()` to remove.
    

**2. The "Missing" Month**

- **Strategy:** You need a "Calendar Table" or a master list of months.
    
- **Solution:** Perform a **LEFT JOIN** from the Calendar table to your Sales table. Use `COALESCE(sales, 0)` in SQL or `.fillna(0)` in Pandas to turn the resulting `nulls` into zeros.
    

**3. The Running Total**

- **SQL:** Use the window function `SUM(signups) OVER (ORDER BY date)`.
    
- **Pandas:** Use `df['signups'].cumsum()`.
    

**4. Fuzzy Joining**

- **Solution:** You can't use a standard join. In Python, I would use the `fuzzywuzzy` or `thefuzz` library to calculate a similarity score. In SQL, I might use the `LIKE` operator with wildcards or **Levenshtein distance** functions if the database supports them.
    

**5. Memory Management (10GB file / 8GB RAM)**

- **Solution:** Use **Chunking**. In Pandas, `pd.read_csv(file, chunksize=100000)` allows you to process the data in small batches. Also, I would specify `dtypes` (e.g., using `int32` instead of `int64`) to save space.
    

**6. Conditional Aggregation**

- **SQL:** ```sql
    
    SELECT
    
    SUM(CASE WHEN status = 'Active' THEN 1 ELSE 0 END) AS Active_Count,
    
    SUM(CASE WHEN status = 'Inactive' THEN 1 ELSE 0 END) AS Inactive_Count
    
    FROM Users;
    

**7. The "Last Known" Value**

- **Pandas:** Use `df['temperature'].ffill()` (Forward Fill).
    
- **SQL:** Use the `LAG()` window function or `LAST_VALUE() IGNORE NULLS` (in supported systems like PostgreSQL/BigQuery).
    

**8. Date Formatting**

- **Pandas:** Use `pd.to_datetime(df['date_column'], errors='coerce')`. This is powerful because it can infer many formats automatically and marks unparseable dates as `NaT`.
    

**9. Top N per Group**

- **SQL:** Use `DENSE_RANK() OVER (PARTITION BY category ORDER BY sales DESC)` and then filter where the rank is `<= 3`.
    

**10. The Pivot**

- **Pandas:** Use `df.pivot(index='Category', columns='Year', values='Value')`.
    
- **SQL:** Use the `PIVOT` function (if available) or a series of `CASE WHEN` statements combined with `MAX()`.
    

---

## Answers: 5 Power BI Scenarios

**1. The Slow Report**

- **Diagnosis:** Use the **Performance Analyzer**.
    
- **Fix:** Reduce the number of visuals on one page, optimize DAX measures (avoiding calculated columns where possible), and ensure the data model is a **Star Schema** to reduce the work the engine has to do during filtering.
    

**2. The Wrong Grand Total**

- **The Cause:** Measures are evaluated in the "Total" context (where no specific row filter is applied), not as a sum of the rows above.
    
- **Fix:** Use the `SUMX` iterator function. For example: `SUMX(Values(Table[Store]), [Average Sales])`.
    

**3. Complex Relationships (Fact to Fact)**

- **The Rule:** Never connect two Fact tables directly.
    
- **Solution:** Create a shared **Dimension Table** (e.g., a "Date" table and a "Region" table). Connect both Fact tables to these Dimensions. This creates a Star Schema and maintains data integrity.
    

**4. Dynamic Comparison**

- **Solution:** Use "Disconnected Tables." Create a separate table for the Baseline Year that has no relationship to the main model. Use `SELECTEDVALUE()` in a DAX measure to capture that year and compare it against the main Date filter.
    

**5. Executive vs. Deep Dive**

- **Solution:** Use **Drill-through** and **Tooltips**. The main page shows the CEO the high-level KPIs. If the Analyst wants more, they can hover over a visual for a "Report Page Tooltip" or right-click to "Drill-through" to a hidden page with the raw data.
    

---
