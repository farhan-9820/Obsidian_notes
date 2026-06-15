
## The Background theory

Because a blockchain is global, sometimes two honest miners on opposite sides of the world (say, one in Iceland and one in Japan) will solve the PoW math puzzle at the exact same millisecond.

For a brief moment, the network splits into a fork:

- The Western world thinks Block A is the truth.
    
- The Eastern world thinks Block B is the truth.


## how PoW solves it 

he rule states: **Nodes must always trust and build upon the chain that has the most cumulative [[Proof of Work]] (electricity/math) baked into it.**

1. The network temporarily accepts both Block A and Block B.
    
2. Miners split up and start working on the next block.
    
3. Whichever group solves the next block first (let's say the group working on Block A) will broadcast their new block.
    
4. Suddenly, the "Block A chain" becomes two blocks long, while the "Block B chain" is still only one block long.
    
5. Because of the rule, all computers instantly see that the Block A chain is longer, abandon Block B entirely, and switch to the longer chain.
