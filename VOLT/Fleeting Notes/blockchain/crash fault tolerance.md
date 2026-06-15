This assumes that nodes are either honest and working, or they completely crash and stop talking. **Nodes never lie.** 

* **Environment:** Trusted environments (like Google’s or Amazon’s internal data centers).

- **Theories used:** [[Paxos protocol]] or [[Raft protocols]].
    
- **Threshold:** Can handle up to **under $50\%$** ($1/2$) of nodes crashing. As long as a simple majority ($50\% + 1$) is alive, consensus is reached.