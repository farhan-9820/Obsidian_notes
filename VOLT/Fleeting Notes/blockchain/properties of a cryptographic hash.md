- **Deterministic:** The same input will _always_ produce the exact same output. If you hash the word "Hello" today and again in ten years, the resulting string will be identical.
    
- **Quick Computation:** The algorithm can calculate the hash value incredibly fast.
    
- **Pre-image Resistance (One-Way):** It is a one-way street. You can easily turn data into a hash, but it is mathematically impossible to take a hash and reverse-engineer it back into the original data.
    
- **Small Changes, Huge Difference (The Avalanche Effect):** If you change even a single character or a comma in the input, the resulting hash changes entirely.