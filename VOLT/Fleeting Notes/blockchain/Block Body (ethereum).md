## The Block Body (The Engine Room)

The body contains the real meat of the block. It splits into two core modules: Consensus Operations and the Execution Payload.

### Module A: Consensus Operations

This contains data required by validators to maintain agreement across the global network:

- **Attestations:** A bundle of cryptographic cryptographic "votes" from other validators confirming that the _previous_ blocks in history are valid.
    
- **Deposits/Withdrawals:** Records of users staking 32 ETH to become new validators, or existing validators withdrawing their earnings.
    
- **Slashing Data:** Evidence of any validator caught trying to cheat or double-sign, used to confiscate their funds.

### Module B: The Execution Payload

This is the legacy "Ethereum 1.0" space where human activity occurs. It includes:

- **Transactions List:** An ordered array of all the value transfers, smart contract executions, and token swaps included in this 12-second window.
    
- **Gas Used & Gas Limit:** The limit sets the boundary for how much total computation the block can handle (target is 30 million gas), and "Gas Used" shows how much was consumed.
    
- **Base Fee Per Gas:** The mandatory burn fee required to get a transaction into the block (calculated automatically based on network congestion).
    
- **Receipts Root:** A cryptographic hash of all transaction receipts, verifying the outcomes (like logs emitted or execution success status) of the transactions inside this block.