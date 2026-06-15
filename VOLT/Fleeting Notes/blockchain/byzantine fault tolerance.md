In distributed systems theory, this is best explained by the **Byzantine Generals Problem** (formulated by Leslie Lamport, Robert Shostak, and Marshall Pease in 1982).

- **The Scenario:** A group of generals surrounds an enemy city. They can only communicate by sending foot messengers.
    
- **The Goal:** They must all agree on a common plan: either **Attack** or **Retreat**. A partial attack is a disaster; they only win if they all act together.
    
- **The Catch:** Some of the generals might be traitors. Traitors will try to actively confuse the loyal generals. For example, a traitor might tell General A "Attack" and General B "Retreat" to split their forces.
    

**The Theoretical Question:** How can the loyal generals reach a guaranteed agreement (consensus) despite the presence of liars and delayed messages?

Computer science proves that if you rely purely on simple messaging, you cannot reach consensus if **$1/3$ or more** of the generals are traitors. A system that can survive this is called **Byzantine Fault Tolerant (BFT)**.