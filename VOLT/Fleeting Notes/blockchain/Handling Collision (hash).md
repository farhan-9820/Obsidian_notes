Because a hash table has a finite number of slots but an infinite number of potential inputs, two different keys will occasionally hash to the exact same slot. This is called a **collision**. Engineers use two main techniques to fix this:

1. **Chaining (Open Hashing):** Each slot in the hash table points to a linked list. If two names hash to Slot 14, they are simply chained together in a list inside that slot.
    
2. **Open Addressing (Closed Hashing):** If Slot 14 is taken, the system uses a systematic probe (like checking Slot 15, 16, 17...) to find the next available empty seat.


