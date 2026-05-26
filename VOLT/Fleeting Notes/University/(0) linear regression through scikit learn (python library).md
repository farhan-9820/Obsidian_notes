#machine_learning
## How to import 
``` python
	from sklearn import datasets, preprocessing, linear_model

	from sklearn.model_selection import train_test_split
```

## using scatter plot to determine if its possible to do linear regression 
```python
	
	plt.scatter(X,y)
```

- Here X and Y are the split dataset from the main dataset 
	- simply put feature 1 = x and feature 2 = y 


## testing and training dataset --> splitting 

```python
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.20, random_state=1867500)
```

[[random_state_python_variable_in_scikit_ML]]


## Model 

### Model initializing ---> [[Linear Regression_model_in_scikit]]
``` python
	
model = linear_model.LinearRegression()

model = model.fit(X_train, y_train)

  

theta0 = model.intercept_

theta1 = model.coef_

print(theta0)

print(theta1)
```

## Training the model and loss data calculation 
[[linear_regression_training and testing_using_scikit]]


## What if the data were non-linear 
[[handling non linear data in linear regression using scikit learn]]


## Normalizing the data in scikit 
[[normalizing data in scikit learn]]
[[when not to normalize the target value (y) in linear regression]]

related --> [[Data Leakage in Linear Regression using Scikit]]

## what is pipeline in scikit learn
[[pipeline defintion in scikit learn ]]