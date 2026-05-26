In Logistic Regression, we are not predicting a continuous value (like house prices), but rather the **probability** ($P$) that a given input belongs to a specific class (e.g., "1" for Yes, "0" for No).

---

## 1. The Logit Link (Why not Linear?)

In Linear Regression, the output is $\hat{y} = \theta^T X$. This can result in any value from $-\infty$ to $+\infty$. However, probabilities must stay between **0 and 1**.

To fix this, we map the linear output through the **Sigmoid (Logistic) Function**:

$$h_\theta(x) = \sigma(\theta^T x) = \frac{1}{1 + e^{-\theta^T x}}$$

- If $\theta^T x$ is a large positive number, $h_\theta(x) \approx 1$.
    
- If $\theta^T x$ is a large negative number, $h_\theta(x) \approx 0$.
    
- If $\theta^T x = 0$, $h_\theta(x) = 0.5$ (the decision boundary).
    

---

## 2. The Cost Function (Log Loss)

We cannot use **Mean Squared Error (MSE)** for Logistic Regression because the Sigmoid function makes the MSE "non-convex" (it has many "fake" bottoms/local minima), making it impossible for Gradient Descent to find the best solution.

Instead, we use **Cross-Entropy Loss** (also called **Log Loss**). For a single data point, the cost is:

$$Cost(h_\theta(x), y) =

\begin{cases}

-\log(h_\theta(x)) & \text{if } y = 1 \

-\log(1 - h_\theta(x)) & \text{if } y = 0

\end{cases}$$

### Why this works:

- If the true label is $y=1$ and the model predicts $1.0$, the cost is $0$.
    
- If the true label is $y=1$ and the model predicts $0.001$, the cost becomes **infinite**, heavily punishing the model for being "confidently wrong."
    

---

## 3. The Objective Function (Optimization)

To train the model, we minimize the **Average Log Loss** across all $m$ training examples:

$$J(\theta) = -\frac{1}{m} \sum_{i=1}^{m} [y^{(i)} \log(h_\theta(x^{(i)})) + (1 - y^{(i)}) \log(1 - h_\theta(x^{(i)}))]$$

To find the optimal $\theta$ values, we use **Gradient Descent**. The update rule looks surprisingly similar to Linear Regression, but $h_\theta(x)$ is now a Sigmoid:

$$\theta_j := \theta_j - \alpha \frac{\partial}{\partial \theta_j} J(\theta)$$

---

## 4. Decision Boundaries

Logistic Regression doesn't just output a curve; it creates a **linear boundary** in the feature space.

- Predict $y=1$ if $h_\theta(x) \geq 0.5$ (which happens when $\theta^T x \geq 0$).
    
- Predict $y=0$ if $h_\theta(x) < 0.5$ (which happens when $\theta^T x < 0$).
    

---

## 5. Summary Checklist for your Notes

1. **Hypothesis:** $P(y=1|x) = \frac{1}{1+e^{-z}}$ where $z = \theta^T x$.
    
2. **Odd Ratio:** $\log(\frac{p}{1-p}) = \theta^T x$ (This is why it's called "Linear" regression on the log-odds).
    
3. **Optimization:** Maximum Likelihood Estimation (MLE) is used to find $\theta$ by minimizing Log Loss.
    
