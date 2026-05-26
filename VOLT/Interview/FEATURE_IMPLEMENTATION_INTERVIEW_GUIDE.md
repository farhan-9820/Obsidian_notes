# Campus Cats — Feature Implementation (Interview & System Design Notes)

This document maps the **Pet Care Management System / Campus Cats** requirements to how they are realized in the **470_Campus_Cats** codebase. The tone is intentionally **theoretical**: suitable for explaining _design intent_, _trade-offs_, and _how you would defend_ choices in a technical interview—not a line-by-line walkthrough.

---

## 1. System context and high-level architecture

**Problem framing.** The application is a **campus stray-cat welfare platform**: users report cats, log care activity, browse adoption content, coordinate volunteers, and let administrators govern data quality and health information.

**Architectural style.** The implementation follows a **classic three-tier web architecture** adapted to the MERN stack:

| Layer                 | Responsibility                                                  | Primary technologies                              |
| --------------------- | --------------------------------------------------------------- | ------------------------------------------------- |
| **Presentation**      | Routing, auth gating in the UI, forms, consumption of REST APIs | React (Vite), React Router, Axios                 |
| **Application / API** | HTTP endpoints, authorization, orchestration, validation        | Express.js, route modules under `backend/routes/` |
| **Data**              | Persistence, schema, relationships                              | MongoDB via Mongoose models in `backend/model/`   |

**Interface contract.** The backend exposes a **RESTful API** with resource-oriented prefixes (`/api/auth`, `/api/cats`, `/api/posts`, …) mounted in `server.js`. This is a **synchronous request–response** model over HTTP; long-running work is limited to **scheduled in-process jobs** (see §8).

**Cross-cutting concerns** worth naming in an interview:

- **Authentication vs authorization**: identity is established with a **JWT**; access rules are enforced with **middleware** (`auth`, `adminOnly`).
- **Media offload**: images are stored in **Cloudinary**, not on the app server—this is a deliberate **separation of concerns** between compute and blob storage.
- **Soft deletion**: cats and posts can be **logically removed** (`deletedAt`) so list queries stay simple while preserving auditability or delayed hard delete.

---

## 2. Authentication and identity (Sprint Feature 1; SRS security baseline)

**What you built (conceptually).** **Stateless session management** using **JSON Web Tokens**: after credential verification, the server signs a payload `{ id, role }` with a shared secret and returns it to the client. Subsequent requests send `Authorization: Bearer <token>`.

**Technical story.**

- **Password storage**: passwords are hashed with **bcrypt** (salted one-way hashing). In an interview, emphasize that you never compare plaintext to stored passwords and never log secrets.
- **Middleware pipeline**: `auth` verifies the JWT, loads the user from MongoDB, attaches `req.user`, and **rejects deleted accounts** (`isDeleted`)—so “soft-deleted” users cannot keep using the API.
- **Role-based access control (RBAC)**: a second middleware, `adminOnly`, encodes the invariant “this route requires `role === 'admin'`.” This is **horizontal privilege separation** between normal users and operators.

**System design angle.** JWTs trade **server-side session storage** for **client-held state**. Benefits: horizontal scaling without sticky sessions. Costs: revocation is harder (you mitigate with short expiry and, at larger scale, token blocklists or rotation). Your stack uses a **1-day expiry**—reasonable for a campus app; enterprise systems often add refresh tokens.

**Relevant code paths:** `backend/routes/auth.js`, `backend/middleware/auth.js`, `backend/model/User.js`.

---

## 3. Profile, dashboard, and account lifecycle (Sprint Feature 2)

**User-visible behavior.** Authenticated users see a dashboard and profile; they can **soft-delete** their own account.

**Technical story.**

- **Profile read**: `GET /api/users/me` returns the current user document (password excluded) already attached by `auth`.
- **Account deletion**: `DELETE /api/users/me` performs a **soft delete**: `isDeleted`, `deletedAt`, and **display-name anonymization** (`name: "Deleted User"`). This is a **privacy/consistency compromise**: content such as posts may remain attributed to a generic label rather than breaking referential threads.

**System design angle.** Soft delete is a pattern for **eventual consistency with human processes** (moderation, appeals) and for **GDPR-style** discussions: you can describe retention vs erasure and what “right to be forgotten” would require next (e.g., cascade anonymization on posts).

**Relevant code paths:** `backend/routes/users.js`, `frontend/src/pages/Dashboard.jsx`, `UserProfile.jsx`, `App.jsx` (`RequireAuth`).

---

## 4. Report a cat (Sprint Feature 3; SRS FR1)

**Domain model.** A new `Cat` enters the system in **`pending`** status with `reportedBy` set to the reporter.

**Technical story.**

- **Multipart upload** flows through Multer middleware, then **Cloudinary upload** in `reportCat` (`catsController`). The cat’s primary `image` is a URL string returned from the CDN.
- **Write path**: single document insert in MongoDB; no distributed transaction needed at this scale.

**System design angle.** Upload is a **two-phase** pattern in practice: accept file → push to object/CDN store → persist metadata. Failure handling matters: in production you’d discuss **idempotency** and **compensating deletes** if DB save fails after upload.

**Relevant code paths:** `backend/routes/cats.js` (`POST /report`), `backend/controllers/catsController.js`, `backend/middleware/upload.js`.

---

## 5. Approve or reject reported cats (Sprint Feature 4; SRS FR10)

**Workflow.** Admins transition `status` from `pending` to `approved` or `rejected`, set `approvedBy`, and trigger **downstream notifications** to the original reporter.

**Technical story.**

- **State machine** (implicit): `pending → approved | rejected`. The implementation is **optimistic**: single `findById` + mutate + `save`.
- **Side effect**: after state change, `notifyCatApproved` / `notifyCatRejected` append an in-app notification to the reporter’s user document.

**System design angle.** This is a **saga-like** micro-pattern: approval is one transaction; notification is a **second write**. In a larger system you might use an **outbox** or message queue for reliable delivery; here, co-located `await` calls keep complexity low and preserve **read-your-writes** semantics for the same request.

**Relevant code paths:** `backend/routes/cats.js` (`PATCH /approve/:id`, `/reject/:id`), `backend/services/notificationService.js`.

---

## 6. Feeding schedule as structured metadata (Sprint Feature 5)

**Concept.** “Feeding schedule” is not a separate collection; it is a **nested subdocument** on `Cat`: frequency, preferred times, food, location.

**Technical story.**

- Admins update via `PATCH /api/cats/:id/feeding-schedule` (protected).
- Public aggregation: `GET /api/cats/schedule/all` returns a **projection** of approved, non-deleted cats with schedule fields—optimized for the feeding calendar UI.

**System design angle.** Embedding avoids joins and matches **aggregate-root** thinking: the cat is the root; schedule is part of its bounded context. The trade-off: if schedules were shared across many cats, normalization would win; here, **1:1** embedding is appropriate.

**Relevant code paths:** `backend/model/Cat.js` (`feedingSchedule`), `backend/routes/cats.js`, `frontend/src/pages/AdminFeedingSchedule.jsx`, `FeedingSchedule.jsx`.

---

## 7. User-submitted feeding events (Sprint Feature 6; SRS FR2, FR12)

**Concept.** Each feeding is an **append-only event** in `feedingHistory[]` with `fedBy`, optional denormalized `fedByName`, `foodType`, `notes`, and `date`.

**Technical story.**

- `POST /api/cats/:id/feed` pushes a subdocument and maintains **`lastFed`** as a **derived field** (updated when the new event is the latest).
- **Denormalization** of `fedByName` optimizes read paths that list history without always populating `User`.

**System design angle.** This is an **event log inside a document**. At scale you might move to an **event store** or time-series DB; for campus scale, embedded arrays with MongoDB’s document model are a pragmatic choice. **Followers** optionally receive notifications—fan-out on write (see §15).

**Relevant code paths:** `backend/routes/cats.js` (`POST /:id/feed`), `notifyCatFollowers` in `notificationService.js`.

---

## 8. Adoption posts: create, list, delete (Sprint Feature 7; SRS FR13-adjacent)

**Concept.** “Adoption campaigns” in the SRS map to **`Post`** entities: rich text, images, likes, comments.

**Technical story.**

- **Create**: multipart images → Cloudinary; URLs + `imagePublicIds` stored for later cleanup.
- **Delete semantics**: **owner** hard-deletes and removes Cloudinary assets; **admin** may **soft-delete** (`deletedAt`) with a documented retention story (cleanup job).
- **Read models**: list endpoints populate `createdBy`, `likes`, `comments.user`.

**System design angle.** Different delete policies for admin vs owner illustrate **policy-driven commands** and **separation of moderation from user autonomy**. Storing `imagePublicIds` supports **referential cleanup** to the CDN—important for cost and compliance.

**Relevant code paths:** `backend/controllers/postsController.js`, `backend/routes/posts.js`, `backend/model/Post.js`, `backend/jobs/cleanupDeletedItems.js`.

---

## 9. Sponsor a cat (Sprint Feature 8; SRS FR6)

**Concept.** Sponsorship is its own **`Sponsorship`** document linking `user`, `cat`, `amount`, and `purpose` (e.g. food vs medical intent).

**Technical story.**

- Validates positive numeric amount and cat existence.
- **Idempotency** is not enforced at the API level—each POST creates a record (acceptable for “pledge log”; payment gateways would be a future integration).

**System design angle.** This is a classic **associative entity** in ER terms. In microservices language, sponsorship could become its own service if payment and tax rules grow; monolith keeps **ACID within MongoDB** for simple consistency.

**Relevant code paths:** `backend/routes/sponsorshipRoutes.js`, `backend/model/Sponsorship.js`.

---

## 10. Notifications (Sprint Feature 9; SRS FR17)

**Concept.** In-app notifications are **embedded subdocuments** on the `User` model, with a **typed enum** (`type`) describing the domain event.

**Technical story.**

- **Single-user write**: `createNotification` uses `$push` on `notifications`.
- **Bulk fan-out**: `createBulkNotifications` and specialized helpers (e.g. `notifyNewAdoptionPost`) use `updateMany` to notify all non-deleted users except the actor.
- **Read API**: `GET /api/notifications` sorts by `createdAt`; unread counts and mark-read endpoints support inbox UX.

**System design angle.** Embedding notifications **co-locates** inbox data with the user (fast reads, no join). Trade-offs: unbounded array growth (mitigate with pagination/archival in production), and this is **not** push/email—it's **pull-based in-app**. In an interview, contrast with **WebSockets**, **FCM/APNs**, or **email workers** driven by the same domain events.

**Relevant code paths:** `backend/model/User.js` (`notificationSchema`), `backend/services/notificationService.js`, `backend/routes/notifications.js`.

---

## 11. Search: cat gallery and feeding views (Sprint Feature 10; SRS FR14)

**Concept.** Search is implemented as **server-side filtering** over the `Cat` collection using **case-insensitive regex** across multiple fields, plus optional filters (location, health, adoption status).

**Technical story.**

- Endpoint: `GET /api/cats/search?query=…&location=…&healthStatus=…&adoptionStatus=…`.
- Gallery and feeding UIs call the same API when the user types a query.

**System design angle.** Regex on multiple fields is **O(n)** in collection scan without indexes—fine for prototype/campus data volumes. At SRS scale (10k cats, &lt;1s search), you’d discuss **MongoDB text indexes**, **Atlas Search**, or a **search replica** (Elasticsearch/OpenSearch). Framing: _correct first, optimize with measured bottlenecks._

**Relevant code paths:** `backend/routes/cats.js` (`GET /search`), `frontend/src/pages/CatGallery.jsx`, `FeedingSchedule.jsx`.

---

## 12. Volunteer requests: user submission (Sprint Features 11–12)

**Concept.** Users submit structured interest via **`VolunteerRequest`**: contact, availability, experience, message, linked to `user`.

**Technical story.**

- `POST /api/volunteer` (authenticated) validates required fields and persists a document.
- Admins list all requests with `populate` on `assignedCats`.

**System design angle.** Treat the volunteer record as a **workflow ticket**: `pending → approved | rejected`, with optional **many-to-many assignment** to cats via `assignedCats[]`. That models real-world “one volunteer, multiple animals” without duplicating volunteer profile rows.

**Relevant code paths:** `backend/routes/volunteer.js`, `backend/model/VolunteerRequest.js`, `frontend/src/pages/Volunteer.jsx`, `AdminVolunteerRequests.jsx`.

---

## 13. Feedback (Sprint Feature 13; SRS FR16)

**Concept.** Users submit free-text feedback stored as **`Feedback`** documents.

**Technical story.**

- `POST /api/feedback` persists `name`, `email`, `message` with `message` required.

**System design angle.** This is a **fire-and-forget channel** into operations. Production hardening would add **rate limiting**, **spam classification**, and **PII minimization**. The route is a good example of a **non-critical path** that should fail soft and never block core flows.

**Relevant code paths:** `backend/routes/feedback.js`, `backend/model/Feedback.js`, `frontend/src/pages/Feedback.jsx`.

---

## 14. Admin volunteer lifecycle: approve, assign, reject, delete (Sprint Feature 14; SRS FR19–20)

**Concept.** Admins mutate volunteer state and **assign cats** to a volunteer; they can **remove** assignments or **delete** the request entirely.

**Technical story.**

- `PATCH /:id/status` restricts to enum values.
- `POST /:id/assign-cat` deduplicates cat IDs in `assignedCats`.
- `DELETE /:volId/remove-cat/:catId` filters the array.
- `DELETE /:id` removes the volunteer request document.

**System design angle.** **Assignment** is a graph: `VolunteerRequest` ↔ `Cat`. Interview topic: **invariant** “assigned cat must exist and be approved”—you validate cat existence on assign. Optional enhancement: invoke `notifyVolunteerApproved` / `notifyCatAssigned` from the same service layer used elsewhere—the **notification service already defines** those event types, which shows intentional **separation of concerns** even if every route is not yet wired.

**Relevant code paths:** `backend/routes/volunteer.js`, `notificationService.js` (helpers).

---

## 15. Social engagement on posts: likes and comments (Sprint Feature 15; SRS FR7 partial)

**Concept.** Likes are an **array of user ObjectIds** on `Post` (set semantics enforced in application code). Comments are **embedded subdocuments** with `user`, `text`, timestamp.

**Technical story.**

- Like toggles membership in `post.likes` (idempotent per user).
- Comments are **rate-limited** via `commentLimiter` middleware—**backpressure** against abuse.

**System design angle.** Embedded comments **bound read latency** for a post page but **complicate** per-comment moderation at huge scale. Likes as an array are simple; an alternative is a `Like` collection for analytics. Mention **CAP** only lightly: MongoDB replica sets give **strong consistency** for single-document updates; cross-document “like count” caches would introduce **eventual consistency**.

**Relevant code paths:** `backend/routes/posts.js`, `backend/middleware/rateLimit.js`, `backend/model/Post.js`.

---

## 16. Admin health management and creating cats (Sprint Feature 16; SRS FR4–5, FR10)

**Concept.** Admins maintain authoritative **health fields** on `Cat` and append **structured health records**; they can also **bootstrap** approved profiles via `POST /api/cats/create`.

**Technical story.**

- `PATCH /:id/health` updates summary fields; **followers** may be notified on `healthStatus` change.
- `POST /:id/health-record` appends typed records (checkup, vaccination, etc.).
- Admin-created cats start **`approved`** with both `reportedBy` and `approvedBy` set to the admin—**bypassing** the citizen reporting workflow.

**System design angle.** You are modeling **two representations of health**: a **current snapshot** (`healthStatus`, flags) and a **temporal history** (`healthRecords`). That mirrors **CQRS-ish** thinking without full separation: optimized read snapshot + append-only history for audit.

**Relevant code paths:** `backend/routes/cats.js`, `backend/model/Cat.js`, `frontend` admin modals/components.

---

## 17. Follow cat profiles and follower notifications (Sprint Feature 17; SRS FR7 bookmark/follow analogue)

**Concept.** `Cat.followers[]` stores user IDs; follow/unfollow mutate that array.

**Technical story.**

- Authenticated follow/unfollow routes.
- `GET /api/cats/:id` uses **optional JWT** (`optionalAuth`) to enrich the payload with `isFollowing` without requiring login for public read—**progressive enhancement** of the API contract.
- Domain events (feeding, health, wishlist, donations) call **`notifyCatFollowers`** for **selective fan-out**.

**System design angle.** Follower lists on the cat document are **read-optimized**; alternative is a `Follow` collection for bi-directional queries. Fan-out-on-write vs fan-out-on-read: you chose **write-time fan-out** into user inboxes for responsiveness at small scale.

**Relevant code paths:** `backend/routes/cats.js` (follow routes, `optionalAuth`, `GET /:id`), `notificationService.js` (`notifyCatFollowers`).

---

## 18. Analytics dashboard (Sprint Feature 18; SRS FR12, monitoring)

**Concept.** Analytics are **computed aggregates** over `Cat.feedingHistory` and related fields—feeding frequency per period, leaderboards, summaries.

**Technical story.**

- Controller loads relevant cats, **filters events in application memory** by date window (`week` / `month` / `year`), and derives metrics (counts, averages, days since last fed).

**System design angle.** This is **online analytical processing (OLAP)** logic executed **online** in the request path—acceptable for moderate data. Interview upgrade path: **pre-aggregated materialized views**, **scheduled ETL** to a warehouse, or **MongoDB aggregation pipeline** pushdown to reduce data movement.

**Relevant code paths:** `backend/controllers/analyticsController.js`, `backend/routes/analytics.js`, `frontend/src/pages/FeedingAnalytics.jsx`.

---

## 19. Wishlist and donations (Sprint Feature 19; SRS wishlist/donation analogue)

**Concept.** Admins create **`WishlistItem`** rows per cat; users record **donations** as embedded entries with quantity and optional notes.

**Technical story.**

- Wishlist CRUD is **admin-gated**; listing can be filtered by query params.
- `POST /api/wishlist/:id/donate` appends to `donations` and calls **`updateQuantityReceived`** on the model (encapsulated domain logic).
- Creating items or donating can **notify cat followers**.

**System design angle.** Donations are **intent records**, not payment captures—again room to plug Stripe/PayPal later. The model uses **embedded donations** for transactional cohesion with the wishlist item lifecycle.

**Relevant code paths:** `backend/routes/wishlist.js`, `backend/model/WishlistItem.js`, `frontend/src/pages/Wishlist.jsx`.

---

## 20. Landing page (Sprint Feature 20)

**Concept.** Public marketing/entry surface separate from authenticated app chrome (`App.jsx` shows `Navbar` only when `token` exists).

**Technical story.** Static React route at `/` delivering narrative and navigation into register/login flows.

**System design angle.** Separating **public** and **authenticated** shells simplifies **caching** and **SEO** concerns for the landing page and reduces bundle requirements for anonymous users (depending on how you code-split).

**Relevant code paths:** `frontend/src/pages/Landing.jsx`, `frontend/src/App.jsx`.

---

## 21. SRS functional requirements 1–20 — compact mapping

| #     | Requirement (abbrev.)            | Implementation anchor                                                                                     |
| ----- | -------------------------------- | --------------------------------------------------------------------------------------------------------- |
| 1     | Report cat + photo + location    | `POST /api/cats/report`, Cloudinary, `Cat` pending                                                        |
| 2     | Feeding updates                  | `feedingHistory`, `POST /:id/feed`                                                                        |
| 3     | Basic medical updates            | User-facing nuance: detailed health is admin-heavy; community notes can live in description/feeding notes |
| 4     | Detailed health / vaccination    | `healthRecords`, `PATCH /:id/health`, `POST /:id/health-record`                                           |
| 5     | (Vet workflows)                  | `Appointment` model, `appointments` routes, scheduled `sendReminders` in `server.js`                      |
| 6     | Adoption application             | Adoption **posts** + contact fields (`Post.contactInfo`)                                                  |
| 7     | Sponsor                          | `Sponsorship` API                                                                                         |
| 8     | Like, comment, bookmark          | Likes/comments on **posts**; **follow** on **cats** as subscription analogue                              |
| 9     | Volunteer registration           | `VolunteerRequest`                                                                                        |
| 10    | Educational content / guidelines | Could map to posts or static UI; not a separate CMS collection in code                                    |
| 11–12 | Vet scheduling                   | Appointments module + reminders                                                                           |
| 13    | Adoption campaigns               | Adoption posts                                                                                            |
| 14    | Searchable gallery               | `/api/cats/search` + gallery UI                                                                           |
| 15    | Announcements                    | Overlap with notifications/posts; no separate `Announcement` collection observed                          |
| 16    | Feedback                         | `Feedback` API                                                                                            |
| 17    | Push/email notifications         | **In-app** notification array; email/push would be an extension                                           |
| 18    | Cat profile detail               | `GET /api/cats/:id` with population                                                                       |
| 19–20 | Volunteer admin                  | Volunteer routes + admin UI                                                                               |

Use this table in interviews to show **traceability** from spec to code while honestly noting **gaps or reinterpretations** (e.g., announcements as posts, bookmark vs follow).

---

## 22. Non-functional requirements — how to discuss honestly

- **Performance / concurrency (5k users, &lt;2s)**: Argue **stateless API**, **CDN for images**, **DB indexing** as next steps; cite load testing you would run (k6, Artillery).
- **Security**: **HTTPS in deployment**, **JWT secret hygiene**, **bcrypt**, **role checks**—and acknowledge **at-rest encryption** of DB is typically an **infrastructure** concern (encrypted volumes, Atlas encryption).
- **Availability (99.5%)**: Single-node app + MongoDB—discuss **replica sets**, **health checks**, **multi-AZ** for production.
- **Accessibility / mobile web**: Responsive React; native apps would be out of scope unless wrapped (e.g., Capacitor).

---

## 23. Closing narrative for interviews

> “We modeled campus cat welfare as a **document-centric domain** in MongoDB: cats and posts are **aggregates** with embedded histories where access patterns are local. The API is a **thin orchestration layer** over Mongoose with **JWT RBAC**. Cross-cutting behaviors—**media**, **notifications**, **cleanup jobs**—are **isolated into services and middleware** so we can evolve them (e.g., swap in-app notifications for a queue-backed email worker) without rewriting core routes.”

That sentence ties **your actual structure** to **vocabulary** interviewers expect: aggregates, orchestration, RBAC, and evolution toward event-driven design.

---
