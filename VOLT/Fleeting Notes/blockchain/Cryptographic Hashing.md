A hash function is a mathematical algorithm that takes an input of any size (a single letter, a book, or a 4K movie) and squishes it into a **fixed-size string of characters** (a fingerprint).

- **Deterministic:** The exact same input will _always_ produce the exact same output.
    
- **Pre-image Resistance (One-Way):** You cannot look at a hash output and guess the original input.
    
- **The Avalanche Effect:** If you change even a single comma or capitalization in the input, the resulting hash changes completely and unpredictably.
    
- **Collision Resistance:** It is statistically impossible for two different inputs to produce the exact same hash output.
    

> **The Isolated Law:** A hash acts as an immutable digital fingerprint. If you know the hash of a file, you can instantly verify if that file has been tampered with, down to a single pixel or character.