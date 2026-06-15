In isolated theory, a consensus algorithm is only successful if it mathematically guarantees two things: **Safety** and **Liveness**.

- **Safety (Nothing bad happens):** All non-faulty nodes must agree on the _exact same value_. If Node A decides the value is "X", Node B cannot decide the value is "Y". In blockchain terms, this prevents double-spending.
    
- **Liveness (Something good eventually happens):** The system cannot freeze. It must eventually make a decision and cannot get stuck in an infinite loop of indecision.