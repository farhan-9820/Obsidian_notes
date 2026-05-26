System design is best understood as a series of "layers."

[[HTTP status codes]]

---

## 1. The Entry Point: DNS and Load Balancing

**The Concept:** Before a request even hits your server, it needs to find it. DNS translates a URL into an IP address, and a Load Balancer (LB) ensures that no single server is overwhelmed.

[[Load Balancing]]

> **Practical Scenario:** Imagine you're launching a viral ticket-booking app. If 100,000 people click "Buy" at the same time, a single server would crash. A Load Balancer like **Nginx** or **AWS ELB** acts as a traffic cop, distributing those users across 20 different servers.

---

## 2. The Traffic Control: API Gateway and Rate Limiting

**The Concept:** The API Gateway is the "front door" of your backend. It handles authentication, routing, and **Rate Limiting**—preventing a single user (or a malicious bot) from making too many requests.

[[API]]
[[REST API]]

> **Practical Scenario:** You have a public weather API. To prevent one person from scraping your data every millisecond and costing you a fortune, you set a rate limit of 100 requests per hour per user.

---

## 3. The Blueprint: Monolith vs. Microservices

**The Concept:** This is how you organize your code. A **Monolith** is one giant codebase; **Microservices** break the app into small, independent functions (e.g., one service for "Users," one for "Payments").

> **Practical Scenario:** On an e-commerce site, if the "Recommendation Engine" service crashes, you still want the "Checkout" service to work so you can make money. Microservices allow this isolation.

---

## 4. The Speed Layer: Caching

**The Concept:** Databases are slow. Caching stores frequently accessed data in memory (RAM) so it can be retrieved almost instantly.

[[caching]]

> **Practical Scenario:** On a social media profile, the "Bio" and "Username" don't change often. Instead of hitting the database every time someone views your profile, you store that info in **Redis**. This reduces the "Read" latency from 50ms to 2ms.

---

## 5. The Truth: Database Selection & Scaling

**The Concept:** You must choose between **Relational (SQL)** for structured, complex queries and **Non-Relational (NoSQL)** for massive scale and flexible data.

[[sharding]]

- **Replication:** Copying data to multiple servers so if one dies, the data isn't lost.
    
- **Sharding:** Splitting a giant table into smaller chunks based on a key (e.g., users A-M on Server 1, N-Z on Server 2).
    

> **Practical Scenario:** For a banking app, you use **PostgreSQL (SQL)** because you need "ACID" compliance—you can't have money disappear during a transfer. For a chat app with billions of messages, you use **Cassandra (NoSQL)** for its ability to handle massive write volumes.

---

## 6. The Asynchronous Layer: Message Queues

**The Concept:** Some tasks take a long time (like generating a PDF or sending 1,000 emails). You shouldn't make the user wait for these. You "queue" the task and handle it in the background.

[[Message Queues_system_design]]

> **Practical Scenario:** When you upload a video to YouTube, the "Upload Successful" message appears quickly. However, the system is still working in the background to compress the video into 480p, 720p, and 1080p. This is managed by a queue like **RabbitMQ** or **Kafka**.

---

## 7. The Safety Net: Observability

**The Concept:** You need to know when things break. This involves **Logging** (what happened?), **Metrics** (how fast?), and **Tracing** (where did the request get stuck?).

> **Practical Scenario:** Your app is slow for users in London but fast in New York. By looking at your **Prometheus** metrics and **Jaeger** traces, you see that the London traffic is hitting a misconfigured database node.

---

## 8. Putting it All Together: The Trade-offs (CAP Theorem)

**The Concept:** In a distributed system, you can't have everything. You must choose between **Consistency** (everyone sees the same data at the same time) and **Availability** (the system is always up, even if the data is slightly old).

> **Practical Scenario:** In a "Like" count on a post, **Availability** is better. It's okay if one person sees 1,001 likes and another sees 1,002. But for a bank balance, **Consistency** is mandatory—you cannot show different balances to the same user.




