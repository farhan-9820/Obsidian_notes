**ERC-20** (Ethereum Request for Comments #20) is the undisputed rulebook for creating **fungible tokens** on Ethereum and all EVM-compatible blockchains (like Polygon, Arbitrum, Optimism, and Base).

Proposed by Fabian Vogelsteller and Vitalik Buterin in late 2015, it acts as a standard template. If your contract includes a specific set of variables and functions, every crypto wallet, exchange, and DeFi app in the world automatically knows how to read your token, display its balance, and transfer it.

## 🏗️ The Anatomy of an ERC-20 Token

Under the hood, an ERC-20 token is really just a glorified **accounting ledger** written in smart contract code. It contains a mapping that maps user addresses to numbers (their balances).


```solidity
mapping(address => uint256) private _balances;
```

To be a valid ERC-20 token, a smart contract **must** implement exactly **6 mandatory functions** and **2 mandatory events**:

### 🔍 The 3 State View Functions (Check Data)

- `totalSupply()`: Returns the total number of tokens that will ever exist for this contract.
    
- `balanceOf(address account)`: Look up exactly how many tokens a specific wallet address holds.
    
- `allowance(address owner, address spender)`: Checks how many tokens a third party (like a decentralized exchange) is allowed to take out of an owner's wallet.
    

### 💸 The 3 Mutation Functions (Move Money)

- `transfer(address to, uint256 amount)`: Moves tokens directly from your wallet to another wallet.
    
- `approve(address spender, uint256 amount)`: Authorizes a smart contract (like Uniswap) to spend a specific number of tokens on your behalf.
    
- `transferFrom(address from, address to, uint256 amount)`: Used by smart contracts _after_ you’ve given them approval. It lets the contract automatically move tokens out of your wallet into a pool or a trade.
    

### 📢 The 2 Mandatory Events (Broadcasting Data)

Whenever one of the transfer or approval functions runs successfully, it must broadcast an event to the blockchain network so apps like MetaMask can instantly update their UI:

- `event Transfer(address indexed from, address indexed to, uint256 value)`
    
- `event Approval(address indexed owner, address indexed spender, uint256 value)`
    

## 🏷️ The Optional (But Practically Mandatory) Metadata

While not strictly required by the underlying protocol, almost 100% of ERC-20 tokens include three extra functions to make them human-readable:

1. **Name:** e.g., `"USD Coin"`
    
2. **Symbol:** e.g., `"USDC"`
    
3. **Decimals:** Usually set to `18` (matching Ethereum's Wei structure) or `6` (common for stablecoins). Blockchains don't deal with fractions, so if a token has 18 decimals, `1.0` token is actually tracked on-chain as the integer `1000000000000000000`.
    

## ⚠️ The Dangerous Flaw of ERC-20

Standard ERC-20 tokens have one major design flaw that has resulted in millions of dollars being lost forever: **They don't check if the receiving address is a smart contract capable of handling them.**

If you accidentally call `transfer()` to send ERC-20 tokens directly to a DeFi pool's contract address instead of using `approve()`, the contract's ledger will update your balance to zero and the pool's balance to higher. However, because the pool contract has no built-in function to handle a direct incoming ERC-20 transfer, those tokens are permanently trapped in limbo forever.

### 🛡️ The Modern Fix: `SafeERC20`

To avoid this and prevent silent failures (where a transfer fails but doesn't roll back the transaction), developers today rarely write raw ERC-20 calls. Instead, they use OpenZeppelin's **`SafeERC20`** library wrappers, which safely revert transactions if something goes wrong.

## 🚀 Common Modern Extensions

Most developers don't build ERC-20s from scratch; they import the baseline standard from the OpenZeppelin library and mix in extensions:

- **`ERC20Burnable`:** Allows users or the owner to permanently destroy tokens, shrinking the total supply.
    
- **`ERC20Capped`:** Enforces a hard limit on the max supply that can ever be minted.
    
- **`ERC20Permit`:** Allows users to sign an off-chain message to approve token spending, saving them gas fees by removing the need to execute an on-chain `approve()` transaction first.









































