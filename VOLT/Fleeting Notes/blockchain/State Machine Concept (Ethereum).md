To a computer theorist, a blockchain running smart contracts is a **Decentralized State Machine**.

1. **The State:** A snapshot of all data, balances, and smart contract variables at a specific millisecond in time ($State_A$).
    
2. **The Input:** A user triggers a smart contract by sending a transaction (e.g., "Deposit 5 tokens").
    
3. **The Transition:** The smart contract code executes mathematically.
    
4. **The New State:** The entire network updates to a new, identical snapshot ($State_B$).
    

$$\text{State}_A + \text{Transaction} \xrightarrow{\text{Smart Contract}} \text{State}_B$$

The smart contract is simply the mathematical formula that dictates exactly how the global state is allowed to change.