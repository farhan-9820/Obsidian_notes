To apply Lasso (L1) Regression in Scikit-Learn, you use the `Lasso` class from the `linear_model` module.

Since Lasso relies on the magnitude of coefficients to apply its penalty, **feature scaling is mandatory**. If your features are on different scales, Lasso will unfairly penalize the features with larger raw values.

---

## 1. Basic Implementation

Here is the standard workflow. The parameter `alpha` represents the regularization strength ($\lambda$).


```python
from sklearn.linear_model import Lasso
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.metrics import mean_squared_error

# 1. Split and Scale (Crucial for Lasso!)
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

scaler = StandardScaler()
X_train_scaled = scaler.fit_transform(X_train)
X_test_scaled = scaler.transform(X_test)

# 2. Initialize and Fit
# alpha=1.0 is the default; higher alpha = more features set to zero.
lasso_model = Lasso(alpha=0.1) 
lasso_model.fit(X_train_scaled, y_train)

# 3. Predict and Evaluate
y_pred = lasso_model.predict(X_test_scaled)
print(f"MSE: {mean_squared_error(y_test, y_pred)}")
```

---

## 2. Using a Pipeline (Recommended)

This is the cleaner, professional way to ensure your scaling and model are locked together, preventing data leakage.


```python
from sklearn.pipeline import Pipeline

lasso_pipeline = Pipeline([
    ('scaler', StandardScaler()),
    ('lasso', Lasso(alpha=0.1))
])

lasso_pipeline.fit(X_train, y_train)
```

---

## 3. How to see Feature Selection in action

The "magic" of Lasso is that it can force coefficients to exactly zero. You can check which features Lasso "deleted" with this code:


```python
import numpy as np

# Get feature names from your DataFrame
feature_names = df.drop('target_column', axis=1).columns
coefficients = lasso_model.coef_

# Pair them up
for name, coef in zip(feature_names, coefficients):
    status = "RETAINED" if coef != 0 else "DROPPED"
    print(f"{name}: {coef:.4f} ({status})")
```

---

## 4. Finding the best Alpha (`LassoCV`)

In your research or projects, choosing `alpha=0.1` is just a guess. Scikit-Learn provides `LassoCV`, which automatically runs cross-validation to find the "perfect" alpha for your specific dataset.


```python
from sklearn.linear_model import LassoCV

# It tests many alpha values and picks the one that minimizes MSE
lasso_cv = LassoCV(cv=5, random_state=42)
lasso_cv.fit(X_train_scaled, y_train)

print(f"Best Alpha found: {lasso_cv.alpha_}")
```

### Summary for your notes:

- **Alpha ($\alpha$):** The tuning parameter. $\alpha=0$ is equivalent to OLS (Linear Regression). High $\alpha$ leads to a very simple model with many zero coefficients.
    
- **Objective:** Minimizes $\text{MSE} + \alpha \times \sum |\text{weights}|$.
    
- **Primary Use:** When you have a high-dimensional dataset and suspect only a few features are actually important.
    
