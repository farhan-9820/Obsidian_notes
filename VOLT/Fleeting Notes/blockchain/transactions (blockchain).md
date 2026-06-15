#cryptography


[[Public Key Cryptography]]

[[Cryptographic Hashing]] 

[[Merkle Tree]]

[[ UTXO vs Account Models]]



## how the transactions happen 


### Step 1: Initiating (UTXO + Public Key Cryptography)

Alice wants to send 1 Bitcoin to Bob. Her wallet looks at the history of the ledger to find her **UTXOs** (her unspent digital coins). She selects a 1.5 BTC UTXO. To unlock this coin, she must prove she owns it. She uses her **Private Key** to generate a digital signature. This signature proves to the world that she owns the public address where that 1.5 BTC is sitting.

### Step 2: Constructing the Outputs (UTXO)

Alice’s transaction destroys her 1.5 BTC UTXO and creates two brand-new outputs:

1. **1.0 BTC** locked to _Bob’s_ Public Key.
    
2. **0.5 BTC** locked back to _Alice’s_ Public Key (her change).
    

### Step 3: Verifying and Fingerprinting (Hashing)

The transaction data (Alice's signature, Bob's public key, the amounts) is run through a **Cryptographic Hash Function**. This turns the entire transaction into a single ID string (e.g., `txid: 9a2f...`). If anyone tries to alter the amount from 1.0 BTC to 10 BTC later, the hash ID will completely break, and the network will reject it.

### Step 4: Packaging the Block (Merkle Trees)

A miner gathers Alice's transaction along with thousands of others. To organize them efficiently, the miner places them all into a **Merkle Tree**. They hash them pair by pair until they get the single **Merkle Root**.

This Merkle Root is placed inside the header of the new block. Because of the mathematical laws of the Merkle Tree, Alice's transaction is now permanently anchored to that block's identity. If anyone ever tries to tamper with Alice's transaction in the future, the Merkle Root will corrupt, the block hash will change, and the entire blockchain will flag it as fraud.

### The Final Synthesis

- **Public Keys** act as the lock and key.
    
- **UTXOs** are the physical cash being melted down and recast.
    
- **Hashing** seals the individual transaction.
    
- **Merkle Trees** bundle thousands of those sealed transactions into a single, un-tamperable block identity.




## questions 

- what if I want to send someone 1 btc and I have 1 btc? 
	-  **scenario A :** I have the exact change. My wallet takes that 1 BTC UTXO and signs it with my private key and sends 1 BTC directly to my friend 


	- **scenario B:** what if the 1 BTC is made of (0.6 + 0.4) BTC ? or I have single chunk of 1.5 BTC ? 
		- If you have a **single 1.5 BTC UTXO** and you want to send someone 1.0 BTC, you cannot simply "slice" that coin in half on the blockchain. **You must spend the whole thing.**

- **The Input:** Your wallet grabs the entire **1.5 BTC UTXO**.
    
- **The Outputs (The Melting & Recasting):** The transaction destroys that 1.5 BTC coin and creates **two brand new coins** simultaneously:
    
    1. A **1.0 BTC coin** sent to your friend's public address.
        
    2. A **0.5 BTC coin** sent right back to a new public address that _you_ control (your change).


> To you, the user, it just looks like you hit "Send 1 BTC" and now you have 0.5 BTC left. But on the blockchain, your old digital coin was completely destroyed, and two brand-new ones were minted.