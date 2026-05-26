**Backend Technical Facts from Your Projects**  
**Complete Summary of All Relevant Backend Concepts, Terms & Technicalities**

Here is a clear, structured, and comprehensive extraction of **every backend-related technical detail** from your two projects (primarily the **Thesis Management System**, with supporting context from the Bitcoin CPD project). This will help you deeply understand backend development principles, architecture, and real-world implementation.

### 1. Overall Backend Architecture & Technology Stack

- **Framework**: **Flask** (lightweight Python micro-framework)  
  - Chosen for its simplicity and full control over routing, sessions, and database interactions.  
  - Follows **MVC-like pattern**: Routes act as Controllers, Jinja2 as Views, MySQL models as Models.

- **Database**: **MySQL** (relational database)  
  - Fully normalized schema derived from EER diagram.  
  - Used raw SQL with parameterized queries (`%s` placeholders) via `cursor`.

- **Core Backend Stack**:
  - **Flask** – routing, request handling, session management.
  - **MySQL** – data persistence with dictionary cursors (`dictionary=True`) for easy template passing.
  - **bcrypt** – password hashing and verification (never stored in plain text).
  - **Werkzeug** – secure file handling (`secure_filename`, `send_from_directory`).
  - **Flask Sessions** – signed cookies with a random secret key for authentication state.
  - **Flash messages** – user feedback after actions (success/error).

**Broad Theory**: This is a **classic monolithic full-stack backend** using server-side rendering. Flask gives you explicit control, making it ideal for learning how every HTTP request maps to database operations, security checks, and response generation.

### 2. Authentication & Authorization System

- **Login Flow**:
  - Role selection (student/faculty/admin) on login page.
  - Route checks role → queries appropriate password table (`Admin`, `StudentPass`, `FacultyPass`).
  - `bcrypt.checkpw(plain_password, hashed_password)` for secure verification.
  - On success: `session['user_id'] = id; session['role'] = 'admin' | 'student' | 'faculty'`.

- **Authorization Middleware**:
  - Every protected route starts with:
    ```python
    if 'role' not in session or session['role'] != 'expected_role':
        return redirect(url_for('login_page'))
    ```
  - Role-based conditional logic in routes and templates.

- **Password Management**:
  - Separate password tables for students and faculty (admin can edit them).
  - `bcrypt.hashpw()` for secure password updates.
  - Admin-only password reset functionality.

**Key Terms**:
- **Session-Based Authentication** (stateful, server-side).
- **Role-Based Access Control (RBAC)**.
- **Password Hashing** with bcrypt (slow, salted, resistant to brute-force).

**Real-World Relevance**: This is a production-grade pattern for secure user management. Using separate password tables follows the **Single Responsibility Principle** and enhances security.

### 3. Database Design & ORM-Like Usage

- **Schema Highlights** (from your normalization report):
  - Normalized to **3NF** (no repeating groups, no partial or transitive dependencies).
  - Core entities: `Student`, `Faculty`, `Group`, `Admin`.
  - Junction tables for multi-valued attributes: `StudentInterests`, `FacultyLinks`, `FacultyConsultationHrs`, `RegSupervisor`, `GroupInterests`.
  - File tables: `GroupFile`, `FacultyFile` with `reply_file_id` for threading.
  - Separate password tables: `StudentPass`, `FacultyPass`.

- **Database Interaction**:
  - Raw SQL with parameterized queries (prevents SQL injection).
  - Dictionary cursors for easy data-to-template mapping.
  - Transactions for atomic updates (e.g., profile edit with multiple junction table changes).
  - Foreign keys for referential integrity.

**Technical Terms**:
- **Normalization** (1NF, 2NF, 3NF).
- **Junction Tables** for many-to-many relationships.
- **Parameterized Queries**.
- **Atomic Operations** (DELETE then INSERT for multi-valued fields).

**Broad Theory**: Proper normalization ensures data integrity and prevents anomalies. Your design demonstrates real-world application of database theory in a web context.

### 4. Core Backend Features & Implementation Details

**a. Profile Editing & Multi-Valued Attributes**
- Routes fetch core data + junction tables.
- On edit: `DELETE` old entries, then loop `INSERT` new ones.
- Atomic updates using transactions.

**b. Group Formation**
- Insert into `Group` table, update student’s `group_id`.
- Pending requests and approval logic with automatic cleanup.

**c. Supervisor Selection & Slot Booking**
- Junction tables (`RegSupervisor`, `Meet`) for requests and bookings.
- On approval: update `Group` table + auto-reject others.
- Time overlap checks for slots.

**d. File Submission & Feedback System**
- `GroupFile` and `FacultyFile` tables with `reply_file_id` for threading (self-referential relationship).
- Werkzeug `secure_filename` + local `/uploads` folder.
- Download route with session authorization.

**e. Admin Features**
- Role-based dashboard with user list.
- Password reset across different tables.

**Key Backend Patterns**:
- **CRUD Operations** with proper authorization checks.
- **Workflow State Management** (pending → approved → rejected).
- **Self-Referential Relationships** for threaded feedback.
- **Event-Driven Consistency** (approval triggers multiple DB updates).

### 5. Security Practices Demonstrated

- **Never store plain passwords** → bcrypt hashing.
- **Parameterized queries** → protection against SQL injection.
- **Session management** with secret key.
- **Authorization checks** on every sensitive route.
- **Secure file handling** (`secure_filename`, MIME checks).
- **Role-based access** enforced server-side.

**Important Terms**:
- **OWASP Top 10 principles** (injection prevention, broken authentication, insecure file upload).
- **Defense in Depth**.

### 6. File Handling & Upload System

- **Backend Flow**:
  - `request.files['file']` → `secure_filename(f.filename)`.
  - Save to `UPLOAD_FOLDER`.
  - Insert `file_link` and metadata into `GroupFile` or `FacultyFile`.
- **Download**: `send_from_directory` with authorization check.
- **Threaded Feedback**: `reply_file_id` creates conversation threads.

**Theory**: Secure file upload is a common vulnerability. Your use of Werkzeug utilities follows best practices.

### 7. Backend Design Patterns & Best Practices

| Concept                        | Implementation in Your Project                     | Why It Matters |
|--------------------------------|----------------------------------------------------|--------------|
| MVC-like Structure             | Routes (Controller), Jinja2 (View), MySQL (Model) | Clear separation of concerns |
| Parameterized SQL              | All queries use `%s` placeholders                  | Security (SQL injection prevention) |
| Atomic Transactions            | Profile edits, group approvals                     | Data consistency |
| Role-Based Authorization       | Session checks on every route                      | Access control |
| Self-Referential Tables        | `reply_file_id` in GroupFile                       | Threaded conversations |
| Flash Messages                 | User feedback after actions                        | Better UX |
| Dictionary Cursors             | Easy data passing to templates                     | Developer productivity |

### 8. Key Backend Terms You Can Confidently Discuss

- **Flask Micro-Framework**
- **Session-Based Authentication**
- **bcrypt Password Hashing**
- **Parameterized Queries**
- **Junction Tables & Normalization (3NF)**
- **Atomic Operations & Transactions**
- **Role-Based Access Control (RBAC)**
- **Self-Referential Relationships**
- **Werkzeug Secure File Handling**
- **Server-Side Rendering Backend**
- **Event-Driven Consistency**
- **CRUD with Authorization**
- **Meta-Learner / Stacking** (from Bitcoin project context – ensemble logic)

These are **all the backend technical facts** directly from your Thesis Management System project. The backend is strong in relational database design, secure authentication, workflow management, and full-stack integration with Jinja2 frontend.

Would you like me to expand any section (e.g., comparison with Django or FastAPI, or how you could improve security/scalability)? Or turn this into interview-style Q&A? Just tell me!