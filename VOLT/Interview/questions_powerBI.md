
Here are 15 questions categorized by topic:

---

### General Concepts & Workflow

**1. What are the three main views in Power BI Desktop?**

- **Report View:** Where you build visualizations.
    
- **Data View:** Where you inspect, clean, and manage data.
    
- **Model View:** Where you manage relationships between tables.
    

**2. What is the typical workflow in Power BI?**

Connect to data (Get Data) → Transform/Clean data (Power Query) → Model data (Relationships/DAX) → Visualize (Reports) → Share (Publish to Power BI Service).

**3. What is the difference between Power BI Desktop and Power BI Service?**

Desktop is a local application used for modeling and report creation. The Service (Pro/Premium) is a cloud-based platform used for sharing, collaborating, and creating dashboards.

**4. What is the difference between a Report and a Dashboard?**

- **Report:** Multiple pages of detailed visuals from a single dataset.
    
- **Dashboard:** A single-page "canvas" (only in PBI Service) that pins "tiles" from one or more reports to show high-level KPIs.
    

---

### Data Connectivity & Transformation

**5. What is Power Query (M Language)?**

Power Query is the "ETL" tool (Extract, Transform, Load). It uses the **M language** to perform data cleaning tasks like renaming columns, changing data types, and merging tables.

**6. Explain the difference between "Import" and "DirectQuery" modes.**

- **Import:** Data is stored in the Power BI cache. It’s very fast but has a size limit (1GB for Pro).
    
- **DirectQuery:** No data is stored; it queries the source in real-time. Best for very large databases or live data.
    

**7. What is "Merge" vs. "Append" in Power Query?**

- **Merge:** Similar to a SQL **JOIN** (adds columns horizontally).
    
- **Append:** Similar to a SQL **UNION** (adds rows vertically).
    

---

### Data Modeling & DAX

**8. What is DAX?**

Data Analysis Expressions. It is a formula language used for creating custom calculations (Measures and Calculated Columns).

**9. What is the difference between a Calculated Column and a Measure?**

- **Calculated Column:** Calculated row-by-row during data refresh and stored in the model (consumes memory).
    
- **Measure:** Calculated on-the-fly based on the filters/visuals currently selected (CPU intensive, preferred for performance).
    

**10. What are the most common DAX functions?**

`SUM`, `AVERAGE`, `MIN`, `MAX`, `COUNTROWS`, and the most powerful one: `CALCULATE` (which modifies the filter context).

**11. What is a "Star Schema" and why is it preferred?**

A design where a central **Fact Table** (numbers/transactions) is connected to multiple **Dimension Tables** (descriptions like Date, Product, Geography). It is optimized for performance in Power BI.

---

### Visualizations & Interactivity

**12. What are "Slicers" and how do they differ from Filters?**

Slicers are on-canvas visual filters that allow users to interactively filter the report. Filters are usually hidden in the "Filter Pane" and can apply to a visual, a page, or the whole report.

**13. What is "Drill-through" in Power BI?**

It allows users to click on a data point in one report page and navigate to a separate, detailed page filtered specifically for that data point.

**14. What are "Bookmarks"?**

Bookmarks capture the current state of a report page (filters, slicers, visual visibility). They are often used to create interactive storytelling or "Reset Filter" buttons.

**15. What is "RLS" (Row-Level Security)?**

A feature that restricts data access for specific users. For example, a manager in Dhaka might only see sales data for the Dhaka region, even if they use the same report as a manager in Chittagong.

---

### Quick Intern Tips:

- **Power Query is your friend:** If you can fix data in Power Query rather than using DAX, do it. It’s better for performance.
    
- **Star Schema:** If an interviewer asks how to improve report speed, "optimizing the data model into a Star Schema" is almost always the right answer.
    


---

# answers --> 


### General Concepts & Workflow

**1. What are the three main views in Power BI Desktop?**

- **Report View:** The canvas where you drag and drop visuals to build your dashboard.
    
- **Data View:** A spreadsheet-like view where you can see the actual data, add calculated columns, and check data types.
    
- **Model View:** Where you manage the relationships (lines) between your tables.
    

**2. What is the typical workflow in Power BI?**

The process usually follows: **Connect** to data → **Transform** data (Power Query) → **Model** data (Relationships/DAX) → **Visualize** (Create charts) → **Publish** (Share to the web via Power BI Service).

**3. What is the difference between Power BI Desktop and Power BI Service?**

- **Desktop:** A free Windows application used for data modeling and creating reports.
    
- **Service:** A cloud-based platform (SaaS) used for sharing reports, creating dashboards, and managing security.
    

**4. What is the difference between a Report and a Dashboard?**

- **Report:** A detailed, multi-page document based on a single dataset.
    
- **Dashboard:** A single-page view (exclusive to the Service) that "pins" the most important visuals from various reports into one place.
    

---

### Data Connectivity & Transformation

**5. What is Power Query (M Language)?**

Power Query is the engine used to clean and transform data before it enters the model. The **M Language** is the formula language used behind the scenes to record every transformation step you take.

**6. Explain the difference between "Import" and "DirectQuery" modes.**

- **Import:** Sucks the data into Power BI’s memory. It is extremely fast but the data is only as fresh as the last refresh.
    
- **DirectQuery:** Leaves data in the source and queries it in real-time. It's slower but handles massive datasets better.
    

**7. What is "Merge" vs. "Append" in Power Query?**

- **Merge:** Adds columns (like a SQL **JOIN**). You combine two tables based on a common column.
    
- **Append:** Adds rows (like a SQL **UNION**). You stack one table on top of another (e.g., combining January sales data with February data).
    

---

### Data Modeling & DAX

**8. What is DAX?**

**Data Analysis Expressions** is a formula language used in Power BI for advanced calculations. It looks similar to Excel formulas but works on tables and columns rather than individual cells.

**9. What is the difference between a Calculated Column and a Measure?**

- **Calculated Column:** Computed at the time of data refresh and stored in the model. Use for filtering or "Slicing."
    
- **Measure:** Computed on-the-fly when you interact with a visual. Use for numeric totals (SUM, AVG).
    

**10. What are the most common DAX functions?**

- `SUM()`, `AVERAGE()`, `COUNTROWS()`
    
- `CALCULATE()`: The most important function; it changes the filter context of a calculation.
    
- `SAMEPERIODLASTYEAR()`: Used for Time Intelligence.
    

**11. What is a "Star Schema" and why is it preferred?**

It is a model where one **Fact Table** (containing numbers/transactions) sits in the middle, surrounded by **Dimension Tables** (containing descriptions like Date, Product, Store). This structure is the most efficient for Power BI to process.

---

### Visualizations & Interactivity

**12. What are "Slicers" and how do they differ from Filters?**

- **Slicers:** Visual objects on the report canvas that users click to filter data.
    
- **Filters:** Settings in the "Filter Pane" that can hide data across a visual, a page, or the whole report without taking up space on the canvas.
    

**13. What is "Drill-through" in Power BI?**

It’s a feature that allows a user to right-click a data point (like "Sales in Dhaka") and navigate to a separate page that shows a detailed breakdown specifically for that region.

**14. What are "Bookmarks"?**

Bookmarks save the current state of a report page. They are used to create "Reset" buttons, navigation menus, or to toggle between different views (like switching from a Bar Chart to a Table view).

**15. What is "RLS" (Row-Level Security)?**

RLS allows you to restrict data access for specific users based on their login. You define "Roles" (e.g., "Sales Manager - Dhaka") so they only see the data rows relevant to them.

---

### Bonus Logic: The ACID of Power BI

If they ask about performance, remember the **Power BI Rule of Thumb**:

1. Do it in the **Source** (SQL) if possible.
    
2. If not, do it in **Power Query** (M).
    
3. If not, do it in **DAX**.
    