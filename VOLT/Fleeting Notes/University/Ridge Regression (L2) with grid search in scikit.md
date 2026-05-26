

# With GridSearchCV 

``` python


log_reg = LogisticRegression(penalty='l2', solver='lbfgs', max_iter=1000, class_weight=class_weights_dict)

param_grid = {'C': [0.001 , 0.01, 0.1, 1]}

  
grid_search = GridSearchCV(estimator=log_reg, param_grid=param_grid, cv=5, scoring='accuracy',verbose=1)
grid_search.fit(x_train_final, y_train_final)

  
print(f"Best C value: {grid_search.best_params_['C']}")
print(f"Best Cross-Validation Accuracy: {grid_search.best_score_:.4f}")
```


# with normal loop 
```  python


from sklearn.linear_model import LogisticRegression

from sklearn.metrics import accuracy_score

  

c_test = [0.0001, 0.001, 0.01, 0.1, 1]

for c_val in c_test:
    model = LogisticRegression(
        penalty='l2',
        C=c_val,
        solver='lbfgs',
        max_iter=1000,
        class_weight=class_weights_dict
    )

    model.fit(x_train_final, y_train_final)
    y_pred_valid = model.predict(x_val)

    acc_validation = accuracy_score(y_val, y_pred_valid)
    print(f'C value = {c_val}; Accuracy = {acc_validation:.4f}')
```


# what is the difference between the two? 


- While these two code blocks look like they are doing the same thing—testing different regularization strengths ($C$)—they differ fundamentally in **how they use your data** and **how they validate the results**.

Think of it this way: the `for` loop is a manual "practice test," while `GridSearchCV` is a "rigorous certification exam."

---

### 1. Cross-Validation vs. Single Split

This is the most significant mathematical difference.

- **The Loop (Single Split):** It trains on your training set and checks the accuracy **once** against your validation set. If that specific 20% validation slice happens to be "easy" or "hard," your results might be biased.
    
- **GridSearchCV (K-Fold):** It ignores your `x_val` during the search. Instead, it takes `x_train_final`, splits it into 5 equal parts (folds), and runs 5 separate experiments for _every_ $C$ value.
    
    - It trains on 4 folds and validates on the 5th.
        
    - It rotates this until every fold has been the "validation" set once.
        
    - The score it gives you is the **average** of those 5 runs, which is much more reliable and less likely to be a fluke.
        

---

### 2. The Final Model

- **The Loop:** After the loop finishes, you have nothing but printed text. If you want to use the best model, you have to manually identify which $C$ was best and re-run the `fit()` command for that specific value.
    
- **GridSearchCV:** It is an **object**. Once `grid_search.fit()` finishes, it automatically identifies the best $C$ and **re-trains a final model** on the _entire_ `x_train_final` dataset. You can immediately call `grid_search.predict()` to use the best version.
    

---

### 3. Purpose in the Pipeline

|**Feature**|**Manual Loop**|**GridSearchCV**|
|---|---|---|
|**Effort**|Low (Quick & Dirty)|Medium (Professional Standard)|
|**Reliability**|Susceptible to "Lucky" splits|Highly Robust (Generalized)|
|**Metric**|Simple Accuracy on one set|Mean Cross-Validation Accuracy|
|**Compute Time**|Faster (1 fit per $C$)|Slower (5 fits per $C$ in this case)|

---

### Summary of the Results

If you run both, you might notice that the "Best C" from the loop and the "Best C" from the Grid Search are different. This happens because the Loop is optimizing for one specific slice of data (`x_val`), while the Grid Search is optimizing for the **general pattern** of the entire training set.

