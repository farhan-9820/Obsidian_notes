In Bitcoin, there is no such thing as an "account balance." Bitcoin uses a system called UTXO (Unspent Transaction Outputs), which is like having a wallet full of different dollar bills that you must constantly break and combine.

Ethereum abandons this. It uses an **Account-Based Model**, which functions exactly like a traditional bank account. Every account on Ethereum has a specific address, and the global blockchain simply keeps a list of these addresses and their current states.

Every Ethereum account contains exactly **four fields**:

1. **Nonce:** A sequential counter tracking how many transactions the account has sent. (This prevents a "replay attack," ensuring a hacker can't broadcast the exact same payment twice).
    
2. **Balance:** The current amount of Ether ($ETH$) the account holds, measured down to its smallest unit, _Wei_ ($1 \text{ ETH} = 10^{18} \text{ Wei}$).
    
3. **Storage Root:** A 256-bit cryptographic hash pointing to the private database memory of the account (used to remember contract variables).
    
4. **Code Hash:** The compiled computer code of the account (if it has any).


#### types of accounts 

[[types of ethereum account]]

