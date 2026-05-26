If your data looks more like a curve than a straight line, standard linear regression will struggle because it's trying to fit a "square peg in a round hole."

To handle non-linear data using Scikit-Learn, you typically use **Polynomial Features**. This technique transforms your original features by raising them to a power (e.g., $x^2, x^3$), which allows a linear model to capture curved relationships.

---

### The Workflow: `PolynomialFeatures`

The most common approach is to use a **Pipeline** to combine the feature transformation and the regression model into one object.

#### 1. Import the tools

Python

```
from sklearn.preprocessing import PolynomialFeatures
from sklearn.linear_model import LinearRegression
from sklearn.pipeline import Pipeline
```

#### 2. Create and Fit the Model

Instead of just `LinearRegression()`, you wrap it in a pipeline:

Python

```
# 'degree=2' means we want to include x-squared terms
model = Pipeline([
    ('poly', PolynomialFeatures(degree=2)),
    ('linear', LinearRegression())
])

model.fit(X, y)
```

### How it works conceptually

When you use `PolynomialFeatures(degree=2)`, the computer takes your input $x$ and creates a new input $x^2$.

- **Original equation:** $y = \theta_0 + \theta_1x$ (Straight line)
    
- **Transformed equation:** $y = \theta_0 + \theta_1x + \theta_2x^2$ (Parabola/Curve)
    

Even though the relationship between $x$ and $y$ is now curved, the relationship between the _parameters_ ($\theta$) is still linear, which is why we can still use a `LinearRegression` solver!

---

### Alternative Methods

If polynomial regression doesn't fit well, you might consider:

1. **Log Transformations:** If your data grows exponentially, try fitting `np.log(y)` or `np.log(X)`.
    
2. **SVR (Support Vector Regression):** Uses kernels to handle complex curves.
    
3. **Splines:** Uses `SplineTransformer` in Scikit-Learn to fit different curves to different sections of the data.
    
