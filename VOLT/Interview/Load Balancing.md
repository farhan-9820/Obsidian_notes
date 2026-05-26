To understand **Load Balancing** theoretically, you have to view it as the mechanism that solves the "Single Point of Failure" and "Resource Exhaustion" problems in distributed systems.

### 1. The Core Objective

At its heart, load balancing is about **High Availability (HA)** and **Reliability**. If you have one server and it goes down, your system is dead. If you have ten servers but all traffic goes to one, your system is still effectively dead. The Load Balancer (LB) ensures that the workload is distributed across a "server pool" or "server farm."

---

### 2. Levels of Operation (OSI Model)

Load balancers typically operate at two different layers of the networking stack:

- **L4 Load Balancing (Transport Layer):** It makes routing decisions based on the IP address and TCP/UDP ports. It doesn't look at the content of the message, making it extremely fast and computationally "cheap."
    
- **L7 Load Balancing (Application Layer):** It is "content-aware." It can look at HTTP headers, cookies, or the URL path.
    
    - _Example:_ It can route requests for `example.com/video` to a server optimized for streaming and `example.com/images` to a storage-optimized server.
        

---

### 3. Load Balancing Algorithms (The Logic)

How does the LB decide which server gets the next request? There are several theoretical strategies:

|**Algorithm**|**Logic**|**Best Use Case**|
|---|---|---|
|**Round Robin**|Requests are sent sequentially (1, 2, 3, then back to 1).|Servers have equal specifications.|
|**Weighted Round Robin**|Servers with higher capacity get a higher percentage of requests.|A mix of powerful and weak servers.|
|**Least Connections**|Sends traffic to the server with the fewest active sessions.|When sessions vary greatly in time/load.|
|**IP Hash**|The user's IP is hashed to determine the server.|When "Session Persistence" (Sticky Sessions) is needed.|

---

### 4. Health Checks

A Load Balancer isn't just a router; it's a monitor. It periodically sends "heartbeats" (small requests) to the backend servers.

- **Active Servers:** If a server responds with a `200 OK`, it stays in the pool.
    
- **Passive/Dead Servers:** If a server fails to respond or returns an error, the LB automatically removes it from the rotation so no users experience a crash.
    

---

### 5. Practical Scenarios

**Scenario A: The Flash Sale (Horizontal Scaling)**

An e-commerce site expects a 1000% increase in traffic at midnight. Theoretically, you can't buy a single CPU powerful enough for this. Instead, you spin up 50 small instances. The Load Balancer uses **Round Robin** to ensure that each instance handles exactly 2% of the load, preventing any single machine from overheating.

**Scenario B: Geographic Routing (Global Load Balancing)**

A user in Dhaka and a user in New York both type `google.com`. A Global Server Load Balancer (GSLB) uses the user's IP location to route them to the nearest data center. This minimizes **latency** (the time it takes for data to travel physically across the ocean).

---

### 6. The "Single Point of Failure" Irony

Theoretically, if the Load Balancer itself dies, the whole system goes down. To solve this, we use **N+1 Redundancy**. You have a "Primary" LB and a "Passive" LB. They share a Virtual IP. If the Primary fails, the Passive LB detects it and takes over the traffic instantly.