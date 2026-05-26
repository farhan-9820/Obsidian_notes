### 2. Why not normalize $y$?

In most regression tasks, we **do not** scale the target variable $y$. Here are the three main reasons:

- **Interpretability:** If $y$ is "Price in Dollars," and you scale it to a range of $0$ to $1$, your model's prediction might be `0.0045`. This is hard to interpret. By leaving $y$ in its original units, your `model.predict()` output is immediately meaningful (e.g., `$450,000`).
    
- **The Math of Linear Regression:** The goal of Linear Regression is to find the relationship $y = \theta X$. If you scale $X$, the model simply adjusts the weights ($\theta$) to compensate. Scaling $y$ doesn't change the "pattern" the model finds; it just changes the scale of the error.
    
- **Predictive Requirements:** When you deploy a model, you want it to tell you the actual value. If you scale $y$ during training, you would have to "un-scale" (inverse transform) every single prediction the model makes in the future, adding unnecessary complexity.
    

---

### 3. When _would_ you normalize $y$?

There are rare cases where you might consider it:

1. **Neural Networks (Deep Learning):** Some activation functions in the output layer (like Sigmoid) only output values between 0 and 1. If your $y$ values are 1,000,000, the network will never reach them without scaling.
    
2. **Extremely Large Ranges:** If your $y$ values vary from $0.00001$ to $1,000,000,000$, a model might struggle with numerical stability. In this case, a **Log Transform** (`np.log(y)`) is usually preferred over Min-Max scaling.