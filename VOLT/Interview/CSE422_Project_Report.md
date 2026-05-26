# CSE422 Lab Project Report

## Obesity Level Classification Using Machine Learning

---

**Course:** CSE422 \- Machine Learning  
**Project:** Obesity Level Classification  
**Date:** 4/1/2025

---

## Table of Contents

1. [Introduction](#1-introduction)  
2. [Dataset Description](#2-dataset-description)  
3. [Dataset Pre-processing](#3-dataset-pre-processing)  
4. [Dataset Splitting](#4-dataset-splitting)  
5. [Model Training & Testing](#5-model-training--testing)  
6. [Model Selection/Comparison Analysis](#6-model-selectioncomparison-analysis)  
7. [Conclusion](#7-conclusion)

---

## 1\. Introduction

This project aims to develop a machine learning system capable of predicting obesity levels in individuals based on various lifestyle and physical attributes. The problem addresses the growing concern of obesity worldwide, which is a significant public health issue affecting millions of people. By analyzing factors such as age, gender, height, weight, dietary habits, physical activity levels, and family history, we can create predictive models that help identify individuals at risk of different obesity levels.

The motivation behind this project stems from the need for early detection and intervention strategies. Healthcare professionals and individuals can benefit from accurate obesity level predictions to make informed decisions about lifestyle modifications, dietary changes, and exercise routines. 

The project employs both supervised learning algorithms (Decision Tree, Naive Bayes, Logistic Regression, and Neural Networks) and unsupervised learning techniques (K-Means clustering) to analyze patterns in the data and make accurate predictions.

---

## 2\. Dataset Description

### Dataset Description

The dataset used in this project is the **Updated Obesity Dataset**, which contains comprehensive information about individuals' physical attributes and lifestyle habits.

#### How many features?

The dataset contains **17 features** in total, consisting of:

- **8 numerical features**: Age, Height, Weight, FCVC (frequency of consumption of vegetables), NCP (number of main meals), CH2O (consumption of water daily), FAF (physical activity frequency), TUE (time using technology devices)  
- **9 categorical features**: Gender, CALC (consumption of alcohol), FAVC (frequent consumption of high caloric food), SCC (calories consumption monitoring), SMOKE (smoking), family\_history\_with\_overweight, CAEC (consumption of food between meals), MTRANS (transportation used), and NObeyesdad (target variable \- obesity level)

#### Classification or regression problem? Why do you think so?

This is a **classification problem**. The target variable `NObeyesdad` contains 7 distinct categorical classes representing different obesity levels:

1. Insufficient\_Weight  
2. Normal\_Weight  
3. Overweight\_Level\_I  
4. Overweight\_Level\_II  
5. Obesity\_Type\_I  
6. Obesity\_Type\_II  
7. Obesity\_Type\_III

Since the output is categorical with discrete class labels rather than continuous numerical values, this is clearly a multi-class classification problem.

#### How many data points?

The dataset contains **2,111 data points** (rows) with 17 columns.

#### What kind of features are in your dataset? (Quantitative / Categorical)

**Quantitative (Numerical) Features (8):**

- Age (float64)  
- Height (float64)  
- Weight (float64)  
- FCVC (float64)  
- NCP (float64)  
- CH2O (float64)  
- FAF (float64)  
- TUE (float64)

**Categorical Features (9):**

- Gender (object) \- 2 unique values  
- CALC (object) \- 4 unique values  
- FAVC (object) \- 2 unique values  
- SCC (object) \- 2 unique values  
- SMOKE (object) \- 2 unique values  
- family\_history\_with\_overweight (object) \- 2 unique values  
- CAEC (object) \- 4 unique values  
- MTRANS (object) \- 5 unique values  
- NObeyesdad (object) \- 7 unique values (target variable)

#### Do you need to encode the categorical variables, why or why not?

**Yes, encoding is necessary** for the following reasons:

1. **Machine learning algorithms require numerical input**: Most ML algorithms (Decision Trees, Neural Networks, Logistic Regression, etc.) cannot directly process categorical text data. They require numerical representations.  
     
2. **Different encoding strategies based on feature type**:  
     
   - **Binary categorical features** (Gender, FAVC, SCC, SMOKE, family\_history\_with\_overweight): Use Label Encoding as they have only 2 categories  
   - **Ordinal features** (CALC, CAEC): Use custom ordinal mapping to preserve the order (no → Sometimes → Frequently → Always)  
   - **Nominal features** (MTRANS): Use One-Hot Encoding since there's no inherent order among transportation methods

   

3. **Target variable encoding**: The target variable `NObeyesdad` is encoded using custom ordinal mapping to represent the progression from insufficient weight to obesity type III.

#### Correlation of all the features (input and output features)

The correlation analysis was performed using multiple methods:

1. **Pearson Correlation** for numerical features: This measures linear relationships between continuous variables  
2. **Spearman Rank Correlation** for numerical features: This captures monotonic relationships and is more robust to outliers  
3. **Cramér's V** for categorical features: This measures association between categorical variables  
4. **Point-Biserial Correlation** for numerical vs. binary categorical features: This measures the relationship between continuous and binary variables

**Key findings from correlation analysis:**

- Strong positive correlation between Height and Weight (expected physical relationship)  
- Moderate correlations between dietary habits (FCVC, NCP, CH2O) and obesity levels  
- Physical activity (FAF) shows negative correlation with obesity levels  
- Technology usage (TUE) shows some correlation with obesity levels  
- Family history with overweight shows significant association with obesity levels

The correlation heatmaps reveal important relationships that help understand which features are most predictive of obesity levels.

#### What do you understand after the correlation test?

After performing the correlation analysis, several important insights emerged:

1. **Physical attributes are highly correlated**: Height and Weight show strong positive correlation, which is expected as they are fundamental physical measurements.  
     
2. **Lifestyle factors matter**: Dietary habits (frequency of vegetable consumption, number of meals, water intake) show meaningful correlations with obesity levels, indicating that eating patterns significantly influence weight status.  
     
3. **Activity levels are important**: Physical activity frequency (FAF) demonstrates negative correlation with obesity, suggesting that more active individuals tend to have lower obesity levels.  
     
4. **Family history is significant**: The categorical correlation analysis shows that family history with overweight has a strong association with the target variable, indicating genetic and environmental factors play a role.  
     
5. **Technology usage impact**: Time spent using technology devices (TUE) shows correlation with obesity levels, possibly indicating sedentary lifestyle patterns.  
     
6. **Feature independence**: Some features show low correlation with each other, suggesting they provide independent information that can be valuable for model training.

### Imbalanced Dataset

#### For the output feature, do all unique classes have an equal number of instances or not?

**No, the classes are not perfectly equal, but the dataset is relatively balanced.**

The distribution of classes in the `NObeyesdad` target variable is as follows:

| Class | Count | Percentage (%) |
| :---- | :---- | :---- |
| Obesity\_Type\_I | 351 | 16.63% |
| Obesity\_Type\_III | 324 | 15.35% |
| Obesity\_Type\_II | 297 | 14.07% |
| Overweight\_Level\_I | 290 | 13.74% |
| Overweight\_Level\_II | 290 | 13.74% |
| Normal\_Weight | 287 | 13.60% |
| Insufficient\_Weight | 272 | 12.88% |

**Analysis:**

- Maximum class percentage: 16.63% (Obesity\_Type\_I)  
- Minimum class percentage: 12.88% (Insufficient\_Weight)  
- Ratio of max to min: 1.29

**Conclusion:** The dataset is relatively balanced across the `NObeyesdad` label classes. The class percentages range from 12.88% to 16.63%, indicating a fair distribution among classes. While not perfectly equal, the imbalance is minimal (ratio of 1.29), which is acceptable for machine learning without requiring extensive balancing techniques like SMOTE. However, stratified sampling during train-test split is still recommended to maintain this balance.

#### Bar Chart Representation

A bar chart was created to visualize the distribution of all 7 classes, clearly showing the relatively balanced nature of the dataset across different obesity levels.

### Exploratory Data Analysis (EDA)

Several exploratory data analysis techniques were applied to extract important relationships from the data:

1. **Skewness Analysis**:  
     
   - Age shows high positive skewness (1.529), indicating a longer tail to the right  
   - NCP shows significant negative skewness (-1.107)  
   - Height and CH2O are approximately symmetrical (skewness close to 0\)

   

2. **Distribution Analysis**:  
     
   - Histograms and density plots were created for all numerical features  
   - Box plots were generated to identify outliers before imputation

   

3. **Categorical Feature Analysis**:  
     
   - Cross-tabulation analysis revealed relationships between categorical features and obesity levels  
   - Gender vs. Obesity Level: Shows that females have higher rates of Obesity Type III (31.11%), while males have higher rates of Obesity Type II (27.61%)  
   - CAEC (eating between meals) vs. Obesity Level: Shows that "Always" eating between meals is associated with Normal Weight (66.04%), while "Frequently" is associated with Insufficient Weight (50%)

   

4. **Weight Distribution by Obesity Level**:  
     
   - Box plots clearly show the progression of weight values across different obesity levels  
   - Weight increases systematically from Insufficient Weight to Obesity Type III

   

5. **Feature Relationships**:  
     
   - The analysis revealed complex interactions between lifestyle factors and obesity levels  
   - Dietary patterns, physical activity, and family history all contribute to obesity classification

---

## 3\. Dataset Pre-processing

### Faults Identified

#### 1\. Null / Missing Values

**Problem:** The dataset contained missing values in three columns:

- **Gender**: 11 missing values  
- **CH2O** (consumption of water daily): 21 missing values  
- **family\_history\_with\_overweight**: 21 missing values  
- **Total missing values**: 53 out of 2,111 records (approximately 2.5%)

**Solution:** Missing values were imputed using appropriate strategies:

- **Gender**: Imputed with the **mode** (most frequent value) since it's a categorical feature with only 2 categories. This preserves the distribution of the feature.  
    
- **CH2O**: Imputed with the **median** value since it's a numerical feature. The median is preferred over the mean for numerical features as it's less sensitive to outliers.  
    
- **family\_history\_with\_overweight**: Imputed with the **mode** (most frequent value) since it's a binary categorical feature.

**Verification:** After imputation, all missing values were successfully handled:

- All 17 columns now have 0 missing values  
- Total missing values after imputation: 0

**Reasoning:**

- Mode imputation for categorical features maintains the original distribution  
- Median imputation for numerical features is robust to outliers  
- The percentage of missing data (2.5%) was small enough that imputation wouldn't significantly bias the dataset

#### 2\. Categorical Values

**Problem:** The dataset contains 9 categorical features that need to be converted to numerical format for machine learning algorithms. Different encoding strategies are required based on the nature of each categorical feature.

**Solution:** Multiple encoding techniques were applied based on feature characteristics:

**a) Label Encoding for Binary Features:** Applied to: Gender, FAVC, SCC, SMOKE, family\_history\_with\_overweight

- These features have only 2 categories  
- Label encoding maps them to 0 and 1  
- Example: Gender: \['Female', 'Male'\] → \[0, 1\]

**b) Custom Ordinal Mapping for Ordinal Features:** Applied to: CALC, CAEC

- These features have inherent order: no → Sometimes → Frequently → Always  
- Custom mapping preserves the ordinal relationship: {'no': 0, 'Sometimes': 1, 'Frequently': 2, 'Always': 3}  
- This encoding maintains the meaningful progression in the data

**c) One-Hot Encoding for Nominal Features:** Applied to: MTRANS (transportation method)

- This feature has 5 categories with no inherent order: Automobile, Bike, Motorbike, Public\_Transportation, Walking  
- One-Hot Encoding creates 5 binary columns: MTRANS\_Automobile, MTRANS\_Bike, MTRANS\_Motorbike, MTRANS\_Public\_Transportation, MTRANS\_Walking  
- This prevents the algorithm from assuming an order that doesn't exist

**d) Target Variable Encoding:** Applied to: NObeyesdad

- Custom ordinal mapping to represent the progression from insufficient weight to obesity:  
  - Insufficient\_Weight: 0  
  - Normal\_Weight: 1  
  - Overweight\_Level\_I: 2  
  - Overweight\_Level\_II: 3  
  - Obesity\_Type\_I: 4  
  - Obesity\_Type\_II: 5  
  - Obesity\_Type\_III: 6

**Result:**

- Original dataset: 17 columns  
- After encoding: 21 columns (MTRANS expanded from 1 to 5 columns)  
- All categorical features successfully converted to numerical format

**Reasoning:**

- Different encoding strategies preserve the semantic meaning of different feature types  
- Ordinal encoding maintains order relationships  
- One-hot encoding prevents false ordering assumptions  
- Label encoding is efficient for binary features

#### 3\. Feature Scaling

**Problem:** The numerical features have different scales and units:

- Age: typically 14-61 years  
- Height: typically 1.45-1.98 meters  
- Weight: typically 39-173 kg  
- Other features have their own ranges

This scale difference can cause algorithms that rely on distance calculations (like Logistic Regression, Neural Networks, K-Means) to be biased toward features with larger magnitudes.

**Solution:** **StandardScaler** was applied to scale the features:

- **For Logistic Regression and Neural Network**: Features were scaled using StandardScaler, which transforms features to have mean=0 and standard deviation=1  
- **Formula**: z \= (x \- μ) / σ  
- The scaler was **fitted on training data only** (X\_train) and then used to transform both training (X\_train\_scaled) and testing (X\_test\_scaled) data  
- This prevents data leakage from test set statistics

**Features scaled:**

- All 20 input features (after encoding) were scaled  
- Target variable (NObeyesdad) was not scaled as it's categorical

**Reasoning:**

- StandardScaler ensures all features contribute equally to distance-based calculations  
- Fitting on training data only prevents information leakage  
- Scaling is essential for algorithms like Logistic Regression and Neural Networks that use gradient-based optimization  
- Decision Tree and Naive Bayes don't require scaling, but it doesn't harm their performance

**Note on Decision Tree and Naive Bayes:**

- Decision Tree: Uses tree-based splitting, not distance-based, so scaling is not required  
- Naive Bayes: Uses probability calculations, not distances, so scaling is not required  
- However, for consistency and to enable fair comparison, all models could use scaled data, but in this project, Decision Tree and Naive Bayes were trained on unscaled data, while Logistic Regression and Neural Network used scaled data.

---

## 4\. Dataset Splitting

### Splitting Strategy

**Method:** **Stratified Random Split**

The dataset was split using `train_test_split` from scikit-learn with the following parameters:

- **test\_size \= 0.2** (20% for testing, 80% for training)  
- **random\_state \= 42** (for reproducibility)  
- **stratify \= y** (to maintain class distribution in both sets)

### Train Set

- **Size:** 1,688 samples (80% of 2,111)  
- **Shape:** (1688, 20\) for features, (1688,) for target  
- **Class Distribution:**  
  - Obesity\_Type\_I: 16.65%  
  - Obesity\_Type\_III: 15.34%  
  - Obesity\_Type\_II: 14.04%  
  - Overweight\_Level\_II: 13.74%  
  - Overweight\_Level\_I: 13.74%  
  - Normal\_Weight: 13.57%  
  - Insufficient\_Weight: 12.91%

### Test Set

- **Size:** 423 samples (20% of 2,111)  
- **Shape:** (423, 20\) for features, (423,) for target  
- **Class Distribution:**  
  - Obesity\_Type\_I: 16.55%  
  - Obesity\_Type\_III: 15.37%  
  - Obesity\_Type\_II: 14.18%  
  - Overweight\_Level\_I: 13.71%  
  - Overweight\_Level\_II: 13.71%  
  - Normal\_Weight: 13.71%  
  - Insufficient\_Weight: 12.77%

### Why Stratified Split?

**Stratified splitting was chosen** because:

1. The dataset has 7 classes with relatively balanced distribution  
2. Stratified split ensures that both training and test sets maintain the same class proportions as the original dataset  
3. This prevents data leakage and ensures fair evaluation  
4. It's especially important for multi-class classification problems to have representative samples of all classes in both sets

The class distributions in both training and test sets closely match the original dataset distribution, confirming that the stratified split worked correctly.

---

## 5\. Model Training & Testing (Supervised)

Four supervised learning models were trained and tested on the obesity classification dataset:

### 5.1 Decision Tree

**Model Configuration:**

- Algorithm: DecisionTreeClassifier from scikit-learn  
- Parameters: Default parameters with random\_state=42  
- Data: Unscaled features (Decision Trees don't require scaling)

**Results:**

- **Accuracy:** 92.43%  
- **Weighted Average Precision:** 92.63%  
- **Weighted Average Recall:** 92.43%  
- **Weighted Average F1-Score:** 92.45%  
- **Weighted Average AUC Score:** 95.60%

**Analysis:**

- Decision Tree performs excellently with 92.43% accuracy  
- Strong performance across all classes, with particularly high precision and recall for obesity types  
- The model shows good generalization with an AUC score of 95.60%  
- Confusion matrix shows minimal misclassifications

### 5.2 Naive Bayes

**Model Configuration:**

- Algorithm: GaussianNB (Gaussian Naive Bayes) from scikit-learn  
- Assumption: Features follow Gaussian distribution  
- Data: Unscaled features (Naive Bayes doesn't require scaling)

**Results:**

- **Accuracy:** 55.79%  
- **Weighted Average Precision:** 61.52%  
- **Weighted Average Recall:** 55.79%  
- **Weighted Average F1-Score:** 50.89%  
- **Weighted Average AUC Score:** 91.24%

**Analysis:**

- Naive Bayes shows the lowest accuracy (55.79%) among all models  
- The model struggles with several classes, particularly Normal\_Weight, Overweight\_Level\_I, and Overweight\_Level\_II  
- However, it performs well on Obesity\_Type\_III (100% precision, 97% recall)  
- The low performance may be due to the violation of the independence assumption (features are likely correlated)  
- Despite low accuracy, the AUC score (91.24%) suggests the model can distinguish between classes to some extent

### 5.3 Logistic Regression

**Model Configuration:**

- Algorithm: LogisticRegression from scikit-learn  
- Solver: 'lbfgs' (Limited-memory Broyden-Fletcher-Goldfarb-Shanno)  
- Multi-class: 'multinomial' (softmax regression)  
- Max iterations: 800  
- Data: **Scaled features** (StandardScaler applied)

**Results:**

- **Accuracy:** 86.76%  
- **Weighted Average Precision:** 86.92%  
- **Weighted Average Recall:** 86.76%  
- **Weighted Average F1-Score:** 86.65%  
- **Weighted Average AUC Score:** 98.22%

**Analysis:**

- Logistic Regression achieves good performance with 86.76% accuracy  
- Excellent AUC score of 98.22%, indicating strong class separation capability  
- Balanced performance across most classes  
- The model shows some difficulty with Normal\_Weight class (67% recall)  
- Feature scaling was crucial for this model's performance

### 5.4 Neural Network

**Model Configuration:**

- Framework: TensorFlow/Keras  
- Architecture:  
  - Input Layer: 20 features  
  - Hidden Layer 1: 128 neurons with ReLU activation  
  - Hidden Layer 2: 64 neurons with ReLU activation  
  - Hidden Layer 3: 32 neurons with ReLU activation  
  - Output Layer: 7 neurons with Softmax activation (for 7 classes)  
- Optimizer: Adam  
- Loss Function: Categorical Crossentropy  
- Metrics: Accuracy  
- Epochs: 50  
- Batch Size: 32  
- Validation Split: 20% of training data  
- Data: **Scaled features** (StandardScaler applied)  
- Target: One-hot encoded

**Results:**

- **Accuracy:** 92.91%  
- **Weighted Average Precision:** 93.11%  
- **Weighted Average Recall:** 92.91%  
- **Weighted Average F1-Score:** 92.93%  
- **Weighted Average AUC Score:** 99.45%

**Training History:**

- The model showed steady improvement over 50 epochs  
- Training accuracy reached \~99% by epoch 50  
- Validation accuracy reached \~92% by epoch 50  
- Loss decreased from \~1.80 to \~0.10 on training set

**Analysis:**

- Neural Network achieves the highest accuracy (92.91%) among all models  
- Exceptional AUC score of 99.45%, the highest of all models  
- Excellent performance across all classes with balanced precision and recall  
- The deep architecture with multiple hidden layers successfully learned complex patterns  
- The model shows strong generalization with consistent performance on test set

### 5.5 Unsupervised Learning: K-Means Clustering

**Model Configuration:**

- Algorithm: KMeans from scikit-learn  
- Number of Clusters: 20 (determined after elbow method analysis)  
- Random State: 42  
- Data: Scaled features (StandardScaler applied to all 20 input features)

**Elbow Method Analysis:**

- The elbow method was applied to determine optimal K  
- Inertia values were calculated for K ranging from 1 to 10  
- The plot showed gradual decrease in inertia, with potential elbow points around K=4 or K=5  
- However, K=20 was chosen for more granular cluster analysis

**Clustering Results:**

- **Silhouette Score:** 0.2247  
  - Interpretation: Closer to \+1 indicates better-defined clusters. A score of 0.22 suggests some cluster separation but with some overlap.  
- **Davies-Bouldin Index:** 1.4938  
  - Interpretation: Lower scores indicate better clustering. A score of 1.49 suggests moderate cluster quality with some compactness and separation.  
- **Calinski-Harabasz Index:** 190.5758  
  - Interpretation: Higher scores indicate better clustering. A score of 190.58 suggests reasonable cluster density and separation.

**Visualization:**

- **2D PCA Visualization:** Principal Component Analysis was applied to reduce dimensions to 2D for visualization. The scatter plot shows the distribution of 20 clusters in the reduced space.  
- **3D PCA Visualization:** PCA was also applied to reduce to 3D, providing a more detailed view of cluster separation in three-dimensional space.

**Analysis:**

- K-Means successfully identified 20 distinct clusters in the data  
- The clustering metrics suggest moderate cluster quality  
- The clusters may correspond to different combinations of lifestyle and physical attributes  
- Some clusters may align with obesity levels, while others may represent other patterns in the data  
- The visualization shows that clusters are somewhat separated but with some overlap, which is expected in high-dimensional data projected to lower dimensions

**Insights:**

- The clustering reveals natural groupings in the data that may not directly correspond to obesity levels  
- Some clusters may represent specific lifestyle patterns (e.g., high activity \+ healthy diet, sedentary \+ poor diet)  
- The moderate silhouette score suggests that while clusters exist, the boundaries are not perfectly distinct, which is common in real-world data

---

## 6\. Model Selection/Comparison Analysis

### 6.1 Overall Model Performance Comparison

The following table summarizes the performance metrics for all supervised learning models:

| Model | Accuracy | Weighted Avg Precision | Weighted Avg Recall | Weighted Avg F1-Score | Weighted Avg AUC Score |
| :---- | :---- | :---- | :---- | :---- | :---- |
| **Neural Network** | **92.91%** | **93.11%** | **92.91%** | **92.93%** | **99.45%** |
| **Decision Tree** | **92.43%** | **92.63%** | **92.43%** | **92.45%** | **95.60%** |
| **Logistic Regression** | **86.76%** | **86.92%** | **86.76%** | **86.65%** | **98.22%** |
| **Naive Bayes** | **55.79%** | **61.52%** | **55.79%** | **50.89%** | **91.24%** |

### 6.2 Accuracy Comparison (Bar Chart)

A bar chart was created comparing the accuracy of all models:

**Observations:**

- **Neural Network** achieves the highest accuracy (92.91%)  
- **Decision Tree** follows closely with 92.43% accuracy  
- **Logistic Regression** shows good performance at 86.76%  
- **Naive Bayes** significantly underperforms with only 55.79% accuracy

The bar chart clearly visualizes the performance gap, with Neural Network and Decision Tree performing similarly well, while Naive Bayes lags behind.

### 6.3 Precision, Recall, and F1-Score Comparison

A grouped bar chart was created comparing Precision, Recall, and F1-Score across all models:

**Key Findings:**

- **Neural Network** shows the best balance across all three metrics (all above 92%)  
- **Decision Tree** demonstrates strong performance with all metrics above 92%  
- **Logistic Regression** shows consistent performance with all metrics around 86-87%  
- **Naive Bayes** shows poor performance with F1-Score at only 50.89%

**Analysis:**

- Neural Network and Decision Tree show excellent precision-recall balance  
- Logistic Regression shows good but lower performance  
- Naive Bayes struggles with precision-recall trade-offs, particularly for intermediate classes

### 6.4 AUC Score Comparison

A bar chart comparing Weighted Average AUC Scores:

**Rankings:**

1. **Neural Network:** 99.45% (highest)  
2. **Logistic Regression:** 98.22%  
3. **Decision Tree:** 95.60%  
4. **Naive Bayes:** 91.24%

**Analysis:**

- All models show strong AUC scores (above 90%), indicating good class separation capability  
- Neural Network's exceptional AUC (99.45%) suggests near-perfect class discrimination  
- Even Naive Bayes, despite low accuracy, shows decent AUC, indicating it can distinguish classes but struggles with exact classification

### 6.5 ROC Curves

Micro-averaged ROC curves were plotted for all models:

**Observations:**

- **Neural Network** shows the best ROC curve, closest to the top-left corner  
- **Logistic Regression** follows closely with excellent curve  
- **Decision Tree** shows strong performance  
- **Naive Bayes** shows decent but lower performance

All models significantly outperform random guessing (diagonal line), with Neural Network and Logistic Regression showing the best true positive vs. false positive trade-offs.

### 6.6 Confusion Matrices

Confusion matrices were generated for each model:

**Decision Tree:**

- Minimal misclassifications  
- Strong diagonal (correct predictions)  
- Some confusion between adjacent classes (e.g., Overweight Level I and II)

**Naive Bayes:**

- Significant misclassifications across multiple classes  
- Many instances misclassified, particularly for Normal\_Weight and Overweight classes  
- Strong performance only for Obesity\_Type\_III

**Logistic Regression:**

- Good diagonal strength  
- Some confusion between similar classes  
- Overall balanced performance

**Neural Network:**

- Strongest diagonal among all models  
- Minimal misclassifications  
- Best class separation

### 6.7 Comprehensive Model Comparison

**Best Overall Model: Neural Network**

- Highest accuracy (92.91%)  
- Highest precision, recall, and F1-score  
- Highest AUC score (99.45%)  
- Best confusion matrix with minimal errors  
- Excellent generalization capability

**Second Best: Decision Tree**

- Very close performance to Neural Network (92.43% accuracy)  
- Simpler model, easier to interpret  
- No need for feature scaling  
- Good performance across all metrics

**Third: Logistic Regression**

- Good performance (86.76% accuracy)  
- Excellent AUC score (98.22%)  
- Requires feature scaling  
- Linear model, interpretable coefficients

**Lowest: Naive Bayes**

- Poor accuracy (55.79%)  
- Struggles with feature independence assumption  
- Despite low accuracy, decent AUC (91.24%)  
- May benefit from feature selection or different assumptions

### 6.8 Key Insights from Comparison

1. **Neural Networks excel** at capturing complex non-linear relationships in the data  
2. **Decision Trees** provide excellent performance with interpretability  
3. **Logistic Regression** offers a good balance of performance and interpretability  
4. **Naive Bayes** struggles due to violated independence assumptions  
5. **Feature scaling** is crucial for Neural Networks and Logistic Regression  
6. **All models** show strong AUC scores, indicating good class separation capability  
7. **The problem** is well-suited for tree-based and neural network approaches

---

## 7\. Conclusion

### 7.1 Understanding from Results

The project successfully developed and evaluated multiple machine learning models for obesity level classification. The results reveal several important insights:

1. **High Performance Achieved**: The best models (Neural Network and Decision Tree) achieved over 92% accuracy, demonstrating that machine learning can effectively predict obesity levels from lifestyle and physical attributes.  
     
2. **Feature Importance**: The correlation analysis and model performance suggest that multiple factors contribute to obesity classification:  
     
   - Physical attributes (Height, Weight) are fundamental  
   - Lifestyle factors (diet, exercise, technology usage) significantly influence outcomes  
   - Family history plays an important role  
   - Dietary patterns (meal frequency, vegetable consumption) are predictive

   

3. **Model Suitability**: Different algorithms show varying levels of success:  
     
   - Neural Networks and Decision Trees excel at this problem  
   - Linear models (Logistic Regression) perform well but may miss non-linear relationships  
   - Naive Bayes struggles due to feature dependencies

   

4. **Data Quality**: The relatively balanced dataset (class distribution ratio of 1.29) contributed to fair model evaluation without requiring extensive balancing techniques.

### 7.2 Performance Comments

**Strengths:**

- **Neural Network** demonstrates exceptional performance with 92.91% accuracy and 99.45% AUC, indicating it successfully learned complex patterns in the data  
- **Decision Tree** provides excellent performance (92.43% accuracy) with the added benefit of interpretability  
- **Logistic Regression** shows solid performance (86.76% accuracy) with good generalization  
- All models show strong AUC scores (above 90%), indicating good class separation capability

**Weaknesses:**

- **Naive Bayes** significantly underperforms (55.79% accuracy), likely due to violated independence assumptions  
- Some models show confusion between adjacent obesity classes (e.g., Overweight Level I vs. II), which is understandable given their similarity  
- The Normal\_Weight class shows lower recall in some models, possibly due to its position between multiple other classes

### 7.3 Why These Results?

Several factors explain the observed results:

1. **Neural Network Success:**  
     
   - The multi-layer architecture can capture complex non-linear relationships  
   - Feature scaling enabled effective gradient-based learning  
   - The sufficient data size (2,111 samples) allowed the model to learn without overfitting  
   - The balanced dataset prevented bias toward majority classes

   

2. **Decision Tree Success:**  
     
   - Tree-based algorithms excel at handling mixed data types (numerical and categorical)  
   - The algorithm can identify important feature splits  
   - No assumptions about data distribution required  
   - Can capture non-linear relationships through hierarchical splitting

   

3. **Logistic Regression Performance:**  
     
   - Feature scaling was crucial for convergence and performance  
   - The multinomial approach handles multi-class classification well  
   - Linear relationships in the data contribute to its success  
   - May miss some non-linear patterns that Neural Networks capture

   

4. **Naive Bayes Underperformance:**  
     
   - The independence assumption is violated (features are correlated, e.g., Height-Weight, dietary habits)  
   - Gaussian assumption may not hold for all features  
   - The model struggles with the complexity of relationships between features and obesity levels

### 7.4 Challenges Faced

Several challenges were encountered during the project:

1. **Missing Data Handling:**  
     
   - Challenge: 53 missing values across 3 features  
   - Solution: Applied appropriate imputation strategies (mode for categorical, median for numerical)  
   - Learning: Choosing the right imputation method is crucial for maintaining data integrity

   

2. **Feature Encoding Complexity:**  
     
   - Challenge: 9 categorical features with different characteristics (binary, ordinal, nominal)  
   - Solution: Applied different encoding strategies based on feature type  
   - Learning: One-size-fits-all encoding doesn't work; understanding feature semantics is important

   

3. **Feature Scaling Requirements:**  
     
   - Challenge: Different models require different preprocessing (scaling vs. no scaling)  
   - Solution: Applied scaling only where necessary (Logistic Regression, Neural Network)  
   - Learning: Understanding algorithm requirements prevents unnecessary preprocessing

   

4. **Model Selection:**  
     
   - Challenge: Choosing between multiple well-performing models  
   - Solution: Comprehensive evaluation using multiple metrics (accuracy, precision, recall, F1, AUC, ROC)  
   - Learning: Single metrics can be misleading; multi-metric evaluation provides better insights

   

5. **Class Imbalance (Minor):**  
     
   - Challenge: Slight imbalance in class distribution (ratio 1.29)  
   - Solution: Used stratified splitting to maintain distribution  
   - Learning: Even minor imbalances should be handled carefully

   

6. **K-Means Clustering Interpretation:**  
     
   - Challenge: Determining optimal number of clusters and interpreting results  
   - Solution: Used elbow method and multiple clustering metrics  
   - Learning: Unsupervised learning requires careful evaluation and may not directly align with supervised labels

   

7. **Neural Network Training:**  
     
   - Challenge: Determining optimal architecture and hyperparameters  
   - Solution: Used a moderate architecture (128-64-32) with validation split  
   - Learning: Balancing model complexity with data size is crucial

   

8. **Multi-class Classification Complexity:**  
     
   - Challenge: 7 classes require careful evaluation metrics  
   - Solution: Used weighted averages and multi-class ROC analysis  
   - Learning: Multi-class problems need specialized evaluation approaches

### 7.5 Future Improvements

Potential areas for future enhancement:

1. **Feature Engineering**: Create interaction features or polynomial features to capture more complex relationships  
2. **Hyperparameter Tuning**: Apply grid search or random search to optimize model parameters  
3. **Ensemble Methods**: Combine predictions from multiple models (voting, stacking)  
4. **Advanced Neural Architectures**: Experiment with dropout, batch normalization, or different architectures  
5. **Feature Selection**: Identify and use only the most important features to reduce complexity  
6. **Cross-Validation**: Use k-fold cross-validation for more robust evaluation  
7. **Handling Naive Bayes**: Try different Naive Bayes variants (Multinomial, Bernoulli) or feature selection  
8. **K-Means Optimization**: Experiment with different K values and initialization methods

### 7.6 Final Remarks

This project successfully demonstrates the application of machine learning to a real-world health classification problem. The results show that with proper data preprocessing, feature engineering, and model selection, high-accuracy predictions are achievable. The Neural Network and Decision Tree models, in particular, show promise for practical applications in healthcare and wellness monitoring systems.

The project highlights the importance of:

- Thorough exploratory data analysis  
- Appropriate preprocessing techniques  
- Understanding algorithm requirements  
- Comprehensive model evaluation  
- Balancing model complexity with interpretability

The insights gained from this analysis can contribute to better understanding of obesity risk factors and support the development of personalized health intervention strategies.

---

**End of Report**  
