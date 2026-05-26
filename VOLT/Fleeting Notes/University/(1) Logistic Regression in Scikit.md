
# Mathematical Definition 
[[logistic regression]]


# Initializing and Training the Model 
```python
from sklearn.linear_model import LogisticRegression
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler

# 1. Split the data
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.20, random_state=42)

# 2. Scaling is CRITICAL for Logistic Regression convergence
scaler = StandardScaler()
X_train_scaled = scaler.fit_transform(X_train)
X_test_scaled = scaler.transform(X_test)

# 3. Initialize the model
# 'liblinear' is a good solver for small datasets
model = LogisticRegression(solver='liblinear', max_iter=100)

# 4. Training
model.fit(X_train_scaled, y_train)
```


# Testing and Prediction 
```python
# Predict the actual class (0 or 1)
y_pred = model.predict(X_test_scaled)

# Predict the probability of belonging to class 1
# This gives you [Prob_Class_0, Prob_Class_1]
y_prob = model.predict_proba(X_test_scaled)[:, 1]
```


# Evaluation Matrix 
```python
from sklearn.metrics import accuracy_score, confusion_matrix, classification_report

# Accuracy: What percentage of total guesses were right?
print("Accuracy:", accuracy_score(y_test, y_pred))

# Confusion Matrix: See exactly where the model got confused
# [True Negatives, False Positives]
# [False Negatives, True Positives]
print("Confusion Matrix:\n", confusion_matrix(y_test, y_pred))

# Classification Report: Precision, Recall, and F1-score
print(classification_report(y_test, y_pred))
```

