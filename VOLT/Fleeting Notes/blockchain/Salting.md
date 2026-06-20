Before hashing your password, the system injects a long string of random characters (the "salt") into it:

$$\text{Password} + \text{Salt} \xrightarrow{\text{Hash Function}} \text{Unique Hash}$$

This ensures that even if two users have the exact same password (like "Password123"), their stored hashes look completely different, rendering hacker databases useless.