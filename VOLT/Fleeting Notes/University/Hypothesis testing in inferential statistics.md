#machine_learning #data_science

In inferential statistics, **hypothesis testing** is a formal procedure used to determine whether a specific claim about a population parameter is supported by sample data. It allows researchers to transition from simply observing data to making "statistically significant" conclusions.

---

### 1. The Core Components

Every hypothesis test involves two competing statements:
- [[Null Hypothesis]]
- [[Alternative Hypothesis]]


### 2. The Testing Process (Confidence, significance and p value)

To decide between these two hypotheses, statisticians follow a structured logic:

- [[confidence in hypothesis testing]]
    
- [[significance level in hypothesis testing]] 
    
- [[p value in hypothesis testing]]



1. **Calculate a Test Statistic:** Depending on the data, you might use a **Z-score, t-score, or F-statistic**. This measures how far your sample results deviate from what the null hypothesis predicted.
    
2. **Determine the P-value:** This is the probability of seeing your sample results (or something more extreme) if the null hypothesis is true.
    

---

### 3. Making the Decision

The conclusion is always based on the relationship between the **P-value** and the **Significance Level ($\alpha$):**

- **If $P \le \alpha$:** You "Reject the Null Hypothesis." The result is **statistically significant**, meaning the observed effect is unlikely to be due to chance alone.
    
- **If $P > \alpha$:** You "Fail to Reject the Null Hypothesis." There is not enough evidence to support the alternative claim.
    

### 4. Common Types of Tests

The choice of test depends on the type of data and the question being asked:

|**Test Name**|**Primary Use Case**|
|---|---|
|**Z-Test**|Comparing a sample mean to a population mean when the population variance is known.|
|**T-Test**|Comparing means when the population variance is unknown (common in small samples).|
|**Chi-Square**|Testing relationships between categorical variables (e.g., does gender affect voting preference?).|
|**ANOVA**|Comparing the means of three or more different groups.|

---

### 5. Possible Errors

Since we are using samples to guess about entire populations, there is always a margin for error:

- **Type I Error ($\alpha$):** A "false positive." You reject the null hypothesis when it was actually true.
    
- **Type II Error ($\beta$):** A "false negative." You fail to reject the null hypothesis when there was actually a significant effect.
    
