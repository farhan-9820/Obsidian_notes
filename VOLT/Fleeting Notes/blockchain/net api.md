### `net` (Network Properties)

A simpler API used to identify the structural environment the node is currently attached to.

- **What it does:** It checks whether the node is actively listening for network connections, counts how many peers it has, and grabs the network ID (e.g., verifying if the DApp is talking to Mainnet, Sepolia, or a local test environment).

### Functions

- Check network status.
- Retrieve network ID.
- Determine peer connectivity.

### Examples

- Verify whether a node is connected.
- Identify whether the node is on Mainnet or a test network.

### Typical Uses

- Network diagnostics.
- Connection verification.
- DApp initialization.