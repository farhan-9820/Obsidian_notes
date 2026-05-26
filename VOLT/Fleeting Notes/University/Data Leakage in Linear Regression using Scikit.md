[[Data Leakage in ML (in scikit)]]

Data leakage is one of the most common "silent killers" in machine learning. It occurs when information from outside the training dataset is used to create the model, leading to overly optimistic performance during testing that fails miserably in the real world.

In **Linear Regression**, this usually happens during the **Feature Engineering** and **Preprocessing** stages.

---

## 1. The Most Common Culprit: Preprocessing Leakage

This happens when you calculate statistics (like Mean or Standard Deviation) using the **entire dataset** before splitting it.

### The Wrong Way (Leakage):

If you call `scaler.fit(X)` on the whole dataset, the scaler "sees" the distribution of the test set. When you later test the model, the model already "knows" the range and average of the test data because those values influenced the scaling of the training data.

### The Correct Way (No Leakage):

You must treat the test set as if it doesn't exist until the very last second.

1. **Fit** the scaler only on `X_train`.
    
2. **Transform** `X_train` using those parameters.
    
3. **Transform** `X_test` using the _same_ parameters from the training set.
    

---

## 2. Target Leakage

This is more subtle and occurs when your features include data that wouldn't actually be available at the time of prediction.

- **Example:** Predicting if a customer will default on a loan. If your features include "Late Fee Charges," you have a leak. A person only gets a late fee _after_ they have already started defaulting. The model will see the late fee and "predict" default with 100% accuracy, but in the real world, you won't know the late fee when the person first applies for the loan.
    

---

## 3. Time-Series Leakage

 On **Time Series Anomaly Detection**, this is the most critical area. In time-series data, the "future" cannot influence the "past."

- **The Leak:** Using `train_test_split(random_state=...)` on time-series data. This shuffles the data, meaning your training set might contain data from Friday to predict what happened on Wednesday.
    
- **The Fix:** Use `TimeSeriesSplit` or a manual split based on a date. You must always train on "Past" data to predict "Future" data.
    

---

## 4. How to Prevent Leakage in Scikit-Learn

The most robust way to prevent leakage is to use a **`Pipeline`**.

A Pipeline encapsulates the "Fit" and "Transform" logic. When you call `pipeline.fit(X_train, y_train)`, Scikit-Learn ensures that the scaler only learns from the training data. When you call `pipeline.predict(X_test)`, it automatically applies the training-set scaling to the test data.


``` python
from sklearn.pipeline import Pipeline
from sklearn.preprocessing import StandardScaler
from sklearn.linear_model import LinearRegression

# This structure makes leakage almost impossible
pipeline = Pipeline([
    ('scaler', StandardScaler()),
    ('model', LinearRegression())
])

pipeline.fit(X_train, y_train) 
# The scaler ONLY sees X_train here.
```

---

## Summary Checklist

- **Split First:** Never do `fit_transform` on the whole `X`.
    
- **Check Temporal Order:** For time-series, ensure `train_index < test_index`.
    
- **Audit Features:** Ask yourself, "Would I actually have this specific piece of data at the exact moment I need to make the prediction?"
    

If your `mse_test` is suspiciously lower than your `mse_train`, or if your $R^2$ is a perfect 1.0, you almost certainly have data leakage.



