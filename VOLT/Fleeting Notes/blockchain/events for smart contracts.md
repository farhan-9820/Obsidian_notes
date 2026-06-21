# Events in Smart Contracts (Ethereum/Solidity)

Events are a mechanism that allows smart contracts to **log information to the blockchain's transaction receipt**. They are primarily used for communication between smart contracts and external applications (frontends, DApps, indexers, analytics systems).

Think of events as:

> "Notifications emitted by a smart contract whenever something important happens."

Unlike contract state variables, events are **not stored as part of the contract's persistent state**. Instead, they are recorded in transaction logs.

---

# Why Events Exist

Suppose you have a token contract.

Without events:

```solidity
balances[msg.sender] -= amount;
balances[to] += amount;
```

The transfer occurs, but external applications must constantly query the blockchain to detect changes.

With events:

```solidity
emit Transfer(msg.sender, to, amount);
```

Applications can immediately detect that a transfer happened.

---

# Basic Syntax

## Declaring an Event

```solidity
event Transfer(
    address from,
    address to,
    uint256 amount
);
```

This only defines the event structure.

---

## Emitting an Event

```solidity
emit Transfer(msg.sender, recipient, amount);
```

This creates a log entry when the transaction executes.

---

# Complete Example

```solidity
// SPDX-License-Identifier: MIT
pragma solidity ^0.8.20;

contract Bank {

    event Deposit(
        address user,
        uint256 amount
    );

    function deposit() public payable {
        emit Deposit(msg.sender, msg.value);
    }
}
```

If someone deposits 5 ETH:

```text
Deposit(
    user = 0x123...
    amount = 5000000000000000000
)
```

will be written to the transaction logs.

---

# How Events Are Stored

Ethereum stores event data inside:

- Transaction receipt
    
- Log entries
    

Not inside:

- Contract storage
    
- State variables
    

This makes events:

✅ Cheaper than storage

❌ Not directly accessible from another smart contract

---

# Event Structure

Example:

```solidity
event ProductPurchased(
    uint256 productId,
    address buyer,
    uint256 price,
    uint256 timestamp
);
```

Contains:

|Field|Type|
|---|---|
|productId|uint256|
|buyer|address|
|price|uint256|
|timestamp|uint256|

---

# Indexed Parameters

One of the most important concepts.

You can mark up to **3 parameters** as indexed.

Example:

```solidity
event Transfer(
    address indexed from,
    address indexed to,
    uint256 amount
);
```

---

## Why Indexed?

Indexed fields become searchable.

Without indexing:

```solidity
event Transfer(
    address from,
    address to,
    uint256 amount
);
```

Finding all transfers involving a specific address would require scanning every log.

With indexing:

```solidity
event Transfer(
    address indexed from,
    address indexed to,
    uint256 amount
);
```

Ethereum can efficiently filter logs.

---

## Example Query

Frontend can ask:

```javascript
contract.queryFilter(
    contract.filters.Transfer(userAddress)
);
```

Only matching logs are returned.

---

# Topics

Under the hood, indexed fields are stored as **topics**.

Ethereum log structure:

```text
Topic 0 = Event Signature
Topic 1 = Indexed Parameter 1
Topic 2 = Indexed Parameter 2
Topic 3 = Indexed Parameter 3
Data    = Non-indexed values
```

---

## Event Signature

Ethereum computes:

```text
keccak256(
"Transfer(address,address,uint256)"
)
```

This hash becomes Topic 0.

Example:

```solidity
event Transfer(
    address indexed from,
    address indexed to,
    uint256 amount
);
```

Ethereum stores:

```text
Topic 0 = Hash of event signature
Topic 1 = from
Topic 2 = to
Data    = amount
```

---

# Accessing Events from Frontend

Using libraries like **Ethers.js**.

## Listening to Events

```javascript
contract.on(
    "Transfer",
    (from, to, amount) => {
        console.log(from, to, amount);
    }
);
```

Whenever the event occurs:

```text
Transfer emitted
```

the callback executes.

---

## Query Past Events

```javascript
const logs =
await contract.queryFilter(
    "Transfer"
);
```

Returns historical event data.

---

# Example: Voting Contract

```solidity
contract Voting {

    event VoteCast(
        address indexed voter,
        uint256 candidateId
    );

    function vote(uint256 id) public {

        emit VoteCast(
            msg.sender,
            id
        );
    }
}
```

Frontend listens:

```javascript
contract.on(
    "VoteCast",
    (voter, candidate) => {
        console.log(
            voter,
            candidate
        );
    }
);
```

---

# Events vs Storage

## Storage Variable

```solidity
uint256 public totalDeposits;
```

Characteristics:

- Persistent
    
- Readable by contracts
    
- Expensive gas cost
    

---

## Event

```solidity
event Deposit(
    address user,
    uint256 amount
);
```

Characteristics:

- Log only
    
- Cheap
    
- Readable by external applications
    
- Not readable by smart contracts
    

---

# Gas Cost Advantage

Writing to storage:

```solidity
balances[user] = amount;
```

is expensive.

Logging:

```solidity
emit Deposit(user, amount);
```

is much cheaper.

This is why analytics data is often stored as events rather than state variables.

---

# Anonymous Events

Normally:

```solidity
event Deposit(
    address user,
    uint256 amount
);
```

stores an event signature.

Anonymous events:

```solidity
event Deposit(
    address user,
    uint256 amount
) anonymous;
```

do not store Topic 0.

Benefits:

- Slightly cheaper gas
    
- One extra indexed parameter available
    

Drawback:

- Harder to identify event type
    

Rarely used.

---

# Event Inheritance

Events can be inherited.

```solidity
contract A {

    event Created(
        address creator
    );
}

contract B is A {

    function create() public {
        emit Created(msg.sender);
    }
}
```

---

# Best Practices

## 1. Emit Events for Important State Changes

Good:

```solidity
emit OwnershipTransferred(
    oldOwner,
    newOwner
);
```

Good:

```solidity
emit Deposit(
    user,
    amount
);
```

Good:

```solidity
emit TokenMinted(
    user,
    amount
);
```

---

## 2. Index Frequently Queried Fields

Good:

```solidity
event Transfer(
    address indexed from,
    address indexed to,
    uint256 amount
);
```

Bad:

```solidity
event Transfer(
    address from,
    address to,
    uint256 amount
);
```

if you plan to search by address.

---

## 3. Don't Use Events as Storage

Bad:

```solidity
emit BalanceUpdated(user, amount);
```

and then assume you can retrieve the balance from within another contract.

Events are logs, not state.

---

## 4. Emit After Successful State Updates

Typical pattern:

```solidity
balances[to] += amount;

emit Transfer(
    msg.sender,
    to,
    amount
);
```

This ensures the event reflects the actual state change.

---

# Common Standard Events

### ERC-20 Tokens

```solidity
event Transfer(
    address indexed from,
    address indexed to,
    uint256 value
);

event Approval(
    address indexed owner,
    address indexed spender,
    uint256 value
);
```

---

### ERC-721 NFTs

```solidity
event Transfer(
    address indexed from,
    address indexed to,
    uint256 tokenId
);

event Approval(
    address indexed owner,
    address indexed approved,
    uint256 tokenId
);

event ApprovalForAll(
    address indexed owner,
    address indexed operator,
    bool approved
);
```

---

# Interview / Exam Definition

> An event in a smart contract is a special logging mechanism that records information in the blockchain transaction logs. Events are emitted during contract execution, can be indexed for efficient searching, and are primarily used by DApps and off-chain applications to monitor and react to smart contract activity.