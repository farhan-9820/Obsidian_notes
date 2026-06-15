How does a computer database track who has what? There are two isolated theories for tracking ledger states:

#### A. The Account-Based Model (e.g., Ethereum, Traditional Banks)

- **The Theory:** Your balance is a single number tied to your identity. If your balance is $50 and someone sends you $20, the database simply overwrites the number to $70.
    

#### B. The UTXO Model (Unspent Transaction Output - e.g., Bitcoin)

- **The Theory:** There are no balances, only "digital cash coins" of various denominations.
    
- If you have $50, you don't actually have a "balance" of $50. You might possess one $20 UTXO and one $30 UTXO.
    
- When you spend money, you don't adjust a balance; you physically destroy old UTXOs and create brand-new ones.
    

> **The Isolated Law:** In a UTXO system, a transaction doesn't say "Subtract $10 from Alice." It says: "Take Alice's existing $50 coin (Input), destroy it, create a new $10 coin for Bob (Output 1), and create a new $40 coin back to Alice as change (Output 2)."