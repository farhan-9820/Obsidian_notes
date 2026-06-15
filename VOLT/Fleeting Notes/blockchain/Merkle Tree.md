Imagine you have a block containing 10,000 transactions. If a user wants to prove their transaction is in that block, they would traditionally have to download and check all 10,000 transactions. Ralph Merkle invented a way to organize data to avoid this.

- **The Structure:** A Merkle Tree is a binary tree of hashes.
    
- You take individual transactions and hash them: $Hash(A)$ and $Hash(B)$.
    
- You combine those hashes and hash them again: $Hash(AB) = Hash(Hash(A) + Hash(B))$.
    
- You repeat this climbing up the tree until you are left with just **one single hash at the top**, called the **Merkle Root**.
    

> **The Isolated Law:** The Merkle Root represents the fingerprint of _all_ transactions below it. If a single transaction at the bottom is altered, the Merkle Root at the top changes completely. This allows a system to prove a transaction belongs in a block by checking only a tiny fraction of the data (called a Merkle Proof).