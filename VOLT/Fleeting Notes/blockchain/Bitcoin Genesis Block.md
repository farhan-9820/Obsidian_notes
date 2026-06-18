

Launched by Satoshi Nakamoto on **January 3, 2009**, Bitcoin's Block 0 established the core economic and cryptographic rules of the network.

- **Previous Block Hash:** `0000000000000000000000000000000000000000000000000000000000000000` (Since it is the first block, there is no prior block to reference; it consists entirely of zeros).
    
- **Transactions:** Exactly **1 transaction**. This is the **Coinbase transaction**, which mints new Bitcoin to reward the miner. It contains a famous message embedded in the hex code (the Coinbase parameter): _"The Times 03/Jan/2009 Chancellor on brink of second bailout for banks"_.
    
- **Block Reward:** **50 BTC**. Interestingly, due to the way Bitcoin's source code was written, this specific 50 BTC reward was hardcoded into the global ledger in a way that makes it unspendable.



> [[ Bitcoin Genesis Block theory]]




- How does processing transactions create a currency? 
	- In a traditional system, a central bank prints physical paper money, and then banks use that money to process transactions. Bitcoin flips this on its head. It uses **transaction processing as the printing press.**

	The protocol relies on a built-in rulebook that everyone agrees to:
	
	1. **The Core Rule:** The software states that anyone who successfully bundles a group of user transactions, solves the cryptographic puzzle, and adds that block to the chain earns the right to write **one special line item** at the top of the block (the Coinbase transaction).
	    
	2. **The "Out of Thin Air" Mechanism:** This line item does not take money away from anyone. The software simply increases the miner's balance. The system literally _defines_ the creation of new currency as the payment for the service of securing the network.



> [[two types of payment for miners (bitcoin blockchain)]]


- Why it doesnt cause hyperinflation? 
	- If a government needs more money, they can just keep printing it infinitely. Bitcoin mathematically prevents this in two ways:

	- **The Hard Cap (Scarcity):** There will only ever be **21 million Bitcoins** in existence. Ever. The software is hardcoded so that once 21 million are "printed" via the puzzle-solving process, the printing press shuts off permanently.
	    
	- **The Halving (Controlled Supply):** The reward given to miners for solving the puzzle automatically **cuts in half every four years**. In 2009, the reward was 50 BTC per block. Today, it is only 3.125 BTC. Over time, the amount of new money entering the system slows to a crawl, making it _deflationary_, not inflationary.
	    
	
	So, while it is created from thin air, it is done on a strict, predictable schedule that **cannot be changed** by any politician or bank.