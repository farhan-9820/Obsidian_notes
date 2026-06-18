
[[Proof of Stake (blockchain)]]

### High Level Architecture 

Every 12 seconds (a "slot"), a validator broadcasts an unified block structure. It is cleanly split into a **Block Header** (metadata) and a **Block Body** (the payload).

[[Block Header (ethereum) | block header]]

[[Block Body (ethereum) | block body]]




### The three tries: Ethereum's Data Secret 

nlike Bitcoin, which only tracks transactions, Ethereum must track complex account memories and contract states. To do this without making block sizes balloon out of control, Ethereum’s execution payload references three specialized [[**Merkle Patricia Tries**]] (advanced cryptographic data trees. 

Execution Payload --> 1. state trie , 2. transactions trie, 3. receipts trie


