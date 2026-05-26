Applying **Ridge Regression (L2 Regularization)** in Scikit-Learn follows a nearly identical pattern to Lasso, but the mathematical impact on your coefficients is different. While Lasso can drop features to zero, Ridge shrinks them all proportionally, which is ideal when you have many features that all contribute a little bit to the prediction.

Just like with Lasso, **feature scaling is mandatory** for Ridge because the penalty is applied to the squared magnitude of the coefficients.

---

## 1. Basic Implementation

In Ridge, the regularization strength is also controlled by the parameter `alpha`.



```python
from sklearn.linear_model import Ridge
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.metrics import mean_squared_error

# 1. Split and Scale
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

scaler = StandardScaler()
X_train_scaled = scaler.fit_transform(X_train)
X_test_scaled = scaler.transform(X_test)

# 2. Initialize and Fit
# alpha=1.0 is default; higher alpha = more weight shrinkage
ridge_model = Ridge(alpha=1.0)
ridge_model.fit(X_train_scaled, y_train)

# 3. Predict and Evaluate
y_pred = ridge_model.predict(X_test_scaled)
print(f"Test MSE: {mean_squared_error(y_test, y_pred)}")
```

---

## 2. Professional Workflow: The Pipeline

Using a `Pipeline` ensures that your `StandardScaler` and `Ridge` model are treated as a single unit, which is much safer for deployment.


```python
from sklearn.pipeline import Pipeline

ridge_pipe = Pipeline([
    ('scaler', StandardScaler()),
    ('ridge', Ridge(alpha=1.0))
])

ridge_pipe.fit(X_train, y_train)
print(f"Model Score: {ridge_pipe.score(X_test, y_test)}")
```

---

## 3. Comparison: Ridge vs. Lasso Coefficients

A great way to understand Ridge is to look at how it treats the coefficients compared to Lasso.


```python
# Ridge coefficients are rarely exactly zero
print("Ridge Coefficients:", ridge_model.coef_)
```

- **Lasso (L1):** Performs "Feature Selection" (some weights become 0).
    
- **Ridge (L2):** Performs "Feature Weighting" (all weights stay, but become very small).
    

---

## 4. Automated Tuning with `RidgeCV`

Instead of guessing the `alpha` value, use `RidgeCV`. It performs an efficient version of Leave-One-Out Cross-Validation to find the best regularization strength.


```python
from sklearn.linear_model import RidgeCV

# Define a list of alphas to test: 0.1, 1.0, 10.0
alphas = [0.1, 1.0, 10.0, 100.0]

ridge_cv = RidgeCV(alphas=alphas, scoring='neg_mean_squared_error')
ridge_cv.fit(X_train_scaled, y_train)

print(f"Best Alpha: {ridge_cv.alpha_}")
```

### Summary for your Notes:

- **Objective:** Minimizes $\text{MSE} + \alpha \times \sum (\text{weights})^2$.
    
- **When to use:** When you have many features with small/medium effects, or when you have **multicollinearity** (features that are highly correlated with each other). Ridge is much more stable than OLS or Lasso when features are correlated.
    



# Ridge Regression with GridSearchCV 
[[Ridge Regression (L2) with grid search in scikit]]

