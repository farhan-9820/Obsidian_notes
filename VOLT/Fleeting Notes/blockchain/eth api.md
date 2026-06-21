### `eth` (Blockchain Interaction)

This is the most heavily used API namespace in all of Web3 development. It is the core window into the ledger's state.

- **What it does:** * **Reads data:** Checks an account balance, gets a block by its number, or reads data from a smart contract.
    
    - **Writes data:** Broadcasts new signed transactions to the network (such as executing a smart contract function or sending Ether).
        
- **Example Functions:** `eth.getBalance()`, `eth.sendRawTransaction()`, `eth.call()`.

### Functions

- Query account balances.
- Send transactions.
- Deploy smart contracts.
- Invoke smart contract functions.
- Retrieve block information.

### Examples

- Get an account balance.
- Send Ether between accounts.
- Read smart contract state.
- Deploy a new contract.

### Typical Uses

- DApp development.
- Wallet applications.
- Blockchain explorers.
- DeFi platforms.