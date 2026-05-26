**Change Point Detection in Bitcoin Time Series – Technical Interview Deep Dive**  
**Ensemble & Deep Hybrid Approaches (Statistical + LSTM Autoencoder with Attention)**

**Interviewer:** Give us a high-level overview of the project and why change point detection (CPD) is particularly challenging for Bitcoin time series.

**You:**  
Bitcoin exhibits extreme non-stationarity, high volatility, fat-tailed distributions, and strong multivariate dependencies with macro variables (SP500, DXY) and on-chain metrics. Traditional CPD methods struggle because they assume piecewise stationarity or require heavy parameter tuning, while Bitcoin has regime shifts driven by both endogenous (halvings) and exogenous (ETF approvals, crashes) events.  

We developed **two complementary unsupervised approaches**:  
- An **ensemble of 8 statistical methods** with weighted voting for robust consensus.  
- A **deep hybrid model** (LSTM Autoencoder + multi-head attention + CUSUM) that learns non-linear representations and detects persistent statistical shifts via reconstruction error.  

**Broad theory:** CPD in financial time series is fundamentally about identifying when the data-generating process changes. Ensemble methods leverage the **wisdom of crowds** (diversity reduces false positives), while deep learning captures long-range temporal dependencies that classical statistics miss. Both are fully unsupervised, aligning with real-world trading where labeled regime data is scarce.

**Interviewer:** Walk through the dataset – what makes this 17-year multivariate Bitcoin series unique for CPD research?

**You:**  
- 6203 daily observations (2009–2025) across 8 features: BTC_Close, BTC_Volume, Hash_Rate, MVRV_Ratio, Unique_Addresses, SP500_Close, DXY_Close, M2SL.  
- No missing values; all numeric.  
- Strong macroeconomic influence (SP500 positive correlation, DXY negative) and on-chain linkage (Hash_Rate ↔ BTC_Close).  

**Broad theory:** Multivariate time series CPD is harder than univariate because shifts can occur in individual dimensions or in their joint distribution. We retained all features (no selection) to preserve diversity, then applied log-returns + RobustScaler to handle non-stationarity and outliers (22.62% anomalies detected).

**Interviewer:** How did you approach Exploratory Data Analysis (EDA) and preprocessing?

**You:**  
- Skewness analysis showed heavy non-normality across most features.  
- Stationarity tests: all series non-stationary except MVRV_Ratio → log-return transformation achieved stationarity for all.  
- Correlation heatmaps (Spearman & Pearson) revealed macro influence and Hash_Rate/BTC_Close linkage.  
- ACF/PACF suggested 60-day windows for deep learning. Preliminary clustering indicated 3–4 regimes.  
- Temporal split (70/15/15) preserved order to avoid leakage.  

**Broad theory:** Non-stationarity masks regime changes, so transformation is critical. RobustScaler was chosen over StandardScaler because financial data has extreme outliers; preserving all features follows the **no free lunch** principle – different algorithms are sensitive to different dimensions.

**Interviewer:** Let’s dive into the Ensemble CPD architecture. Why combine 8 methods?

**You:**  
No single algorithm captures all types of shifts (mean, variance, distribution, regime transitions). We grouped them:  
- **Core methods (weight 2.0)**: CUSUM (mean shifts), RuLSIF & KLIEP (density ratios), SWAB (clustering-based), MDL (information-theoretic segmentation).  
- **Probabilistic (weight 1.5)**: HMM and GMM for latent state modeling.  
- **Non-parametric (weight 1.0)**: k-NN for local density anomalies.  

**Broad theory:** Ensemble learning in CPD exploits **algorithmic diversity** – parametric, non-parametric, information-theoretic, and probabilistic methods see different aspects of the same data. Weighted voting with minimum consensus (≥2 methods) and ±30-day merging reduces false positives and handles gradual regime transitions.

**Interviewer:** How does the weighted voting and consensus mechanism actually work in practice?

**You:**  
Each method outputs candidate change points. We apply a **weighted voting system** and require consensus from at least 2 methods. Detections within ±30 days are merged using median aggregation. This produced 22 consensus change points with average agreement of 3.95 methods per point.

**Broad theory:** This is **meta-learning via consensus**. It mitigates individual model weaknesses (e.g., CUSUM is sensitive to mean shifts but misses distribution changes) while amplifying signal. The tolerance window accounts for market inertia – regime shifts in crypto are rarely instantaneous.

**Interviewer:** Can you break down one core method, say CUSUM, and explain its role in the ensemble?

**You:**  
CUSUM detects mean shifts by accumulating deviations from a target mean. In the ensemble, it provides a simple, fast baseline for abrupt level changes (e.g., crash events). Its high weight (2.0) reflects reliability for mean-based regimes.

**Broad theory:** CUSUM is rooted in sequential hypothesis testing (Page, 1954). When combined with density-ratio methods like RuLSIF/KLIEP, the ensemble covers both **first-order (mean)** and **higher-order (distribution)** shifts.

**Interviewer:** Now let’s talk about the Deep Hybrid CPD. Why LSTM Autoencoder + Attention?

**You:**  
LSTM captures long-term temporal dependencies that statistical methods miss. The autoencoder learns a compressed representation of 60-day windows; high reconstruction error signals a regime shift. Attention (4 heads) highlights which timestamps contribute most to anomalies, adding explainability.

**Broad theory:** Autoencoders are classic for anomaly detection via reconstruction error (Malhotra et al., 2016). LSTM handles sequential data naturally (Hochreiter & Schmidhuber, 1997). Attention mechanisms (inspired by transformers) provide **temporal interpretability** – we can see which past observations drive the current shift.

**Interviewer:** Describe the full hybrid detection pipeline step-by-step.

**You:**  
1. Train LSTM AE (2 layers: 64→32 units encoder, mirrored decoder) on 60-day windows.  
2. Compute reconstruction errors on full series.  
3. Smooth errors (7-day rolling mean) and normalize with MAD.  
4. Apply two-sided CUSUM (threshold=8, drift=1.0) on normalized errors.  
5. Hybrid score = 0.6 × AE error (non-linear patterns) + 0.4 × CUSUM (persistent shifts).  

This yielded 19 change points.

**Broad theory:** Pure autoencoder detection is sensitive to noise; CUSUM adds statistical rigor for **persistent deviations**. The 60/40 weighting prioritizes deep learning’s strength in subtle non-linear regime changes while using classical statistics for confirmation.

**Interviewer:** How does the training setup ensure the model generalizes to unseen Bitcoin regimes?

**You:**  
- Adam optimizer (lr=0.001), MSE loss, batch size 32, 50 epochs + early stopping.  
- Callbacks: EarlyStopping, ReduceLROnPlateau, ModelCheckpoint.  
- Temporal 70/15/15 split prevents leakage.  
- Window size 60 days from ACF/PACF analysis.

**Broad theory:** Temporal splits and early stopping prevent overfitting to past regimes. The memory-free online inspiration (Zhang et al., 2022) was adapted for offline batch processing, balancing computational efficiency with adaptability.

**Interviewer:** How do you validate both approaches against known Bitcoin events?

**You:**  
Eight ground-truth events (4 halvings, COVID crash, ATH, bear bottom, ETF approval). A detection within ±60 days counts as success (accounting for gradual market response). Both methods achieved **100% validation success** and fell within the target 18–25 change points for 17 years.

**Broad theory:** External validation against real economic shocks is the gold standard when ground-truth labels are unavailable. The tolerance window reflects the **market absorption time** of regime changes.

**Interviewer:** Feature importance – how did you quantify which variables drive regime changes?

**You:**  
- Ensemble: Permutation importance + SHAP values.  
- Deep hybrid: Per-feature reconstruction error analysis.  

Top drivers: SP500_Close and DXY_Close (macro), followed by BTC_Close. On-chain metrics (Hash_Rate, MVRV) were less dominant.

**Broad theory:** Macro variables often act as **leading indicators** for crypto regimes. Reconstruction error per feature in the AE acts as a natural importance measure – features that are hardest to reconstruct during shifts are the most regime-sensitive.

**Interviewer:** Compare the two approaches head-to-head – strengths, weaknesses, and complementarity.

**You:**  
- **Ensemble**: More change points (22), higher interpretability via method agreement, robust to different shift types.  
- **Deep hybrid**: Fewer points (19), excels at subtle non-linear patterns, provides temporal attention weights.  
Both detected all 8 events perfectly. They are complementary: ensemble for broad coverage, deep for nuanced detection.

**Broad theory:** No free lunch theorem applies – ensembles reduce variance through averaging, while deep models reduce bias through representation learning. Their agreement validates the detected regimes.

**Interviewer:** Explain the XAI techniques used in each approach.

**You:**  
- **Ensemble**: Agreement heatmap across methods + SHAP for method contribution.  
- **Deep hybrid**: Multi-head attention weights (shows influential past timesteps) + per-feature reconstruction error bar plots + visualization of input vs reconstructed series at change points.

**Broad theory:** Attention provides **post-hoc interpretability** without sacrificing performance. SHAP quantifies feature/method importance in a game-theoretic sense.

**Interviewer:** What were the key results and how do they align with your hypotheses?

**You:**  
- Ensemble: 22 points, avg. 3.95 methods agreement.  
- Deep hybrid: 19 points, stable training (final val loss ~18).  
- 100% event detection success.  
- Macro features (SP500, DXY) dominant – supports hypothesis that macroeconomic drivers outweigh on-chain metrics for major regimes.

**Broad theory:** Results confirm that **hybrid statistical + deep** approaches outperform single-method baselines in volatile, non-stationary domains.

**Interviewer:** Any broader theoretical insights or limitations?

**You:**  
- Ensemble methods shine when you want robustness without deep computational cost.  
- Deep hybrid demonstrates that representation learning + classical statistics is powerful for financial CPD.  
- Limitation: Offline nature; future work could extend to truly online/streaming detection.  
- Ethical note: All public data, fully reproducible, no labeling bias.

**Interviewer:** Final thoughts on how this advances financial time series analysis?

**You:**  
This work bridges classical statistics and modern deep learning for CPD in one of the most challenging assets. By validating against real events and providing strong explainability, it offers practitioners actionable regime detection tools while advancing the theoretical understanding of multivariate non-stationary processes.

**End of Technical Interview Document**  
(Expanded with significantly more questions for depth – ready to copy as `Bitcoin_CPD_Technical_Interview.md`)