- both are 42-character text strings starting with `0x`

Crucially, Ethereum splits this model into two distinct flavors:

|**Externally Owned Accounts (EOAs)**|**Contract Accounts**|
|---|---|
|**Controlled by:** A human using a private key (like a MetaMask wallet).|**Controlled by:** Its own internal software code.|
|**Code Hash:** Empty (no code).|**Code Hash:** Contains the logic of the Smart Contract.|
|**Action:** **Can** actively initiate a transaction.|**Action:** Can only move or react _after_ being triggered by a transaction.|