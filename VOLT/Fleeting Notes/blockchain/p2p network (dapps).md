Once multiple nodes are initialized, they are still isolated islands. They need to be linked together into a **Peer-to-Peer (P2P) Network** so they can synchronize data.

This is done using two main pieces of data:

- **Network ID / Chain ID:** This is a unique number assigned to the blockchain network. For example, Ethereum Mainnet is ID `1`, Sepolia Testnet is `11155111`. If you are making a private network, you might assign it `1234`. Nodes will strictly reject connections from any node using a different Network ID.
    
- **Enode URLs (Bootnodes):** An `enode` is the cryptographic address and IP address of a node. To connect Node B to Node A, you tell Node B to "peer" or connect to Node A's specific enode address.
    

Once connected, the nodes form a mesh network. When a smart contract is deployed or a transaction is made on Node A, it instantly broadcasts that data to Node B, achieving decentralized synchronization.