

## Model Training  

```python
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.20, random_state = 100)

model = linear_model.LinearRegression()
model = model.fit(X_train, y_train)
y_predict = model.predict(X_test)

  
theta0 = model.intercept_
theta1 = model.coef_

print(theta0)
print(theta1)

```

## Model Testing (using MSE)

```python
mse_train = np.mean((y_train - model.predict(X_train))**2)
print("Training loss:", mse_train)

#y_predicted = model.predict(X_test)

mse_test = np.mean((y_test - y_predicted)**2)
print("Testing loss:", mse_test)
```

