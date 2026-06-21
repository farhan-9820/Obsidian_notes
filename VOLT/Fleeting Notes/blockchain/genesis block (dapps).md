A blockchain is a chronological chain of blocks. But how does it start? It starts with **Block 0**, known as the **Genesis Block**.

To launch a private or custom blockchain, you must create a configuration file (usually a JSON file called `genesis.json`). This file defines the initial rules of your custom network, such as:

- **Difficulty:** How hard it is to mine or validate a block.
    
- **Gas Limit:** The maximum amount of computational work allowed per block.
    
- **Allocated Funds:** Pre-funding certain wallet addresses with fake/test ether at the very start of the network.


**"Initializing"** means running a command (like `geth init`) that reads this JSON file and writes Block 0 to the node's database. **Crucial rule:** Every single node that wants to join this specific network _must_ initialize using the exact same genesis block, or they won't be able to talk to each other.