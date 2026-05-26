**Thesis Management System – Technical Interview Deep Dive**  
**Project Overview & Architecture (Flask + MySQL Full-Stack)**

**Interviewer:** Walk me through the high-level architecture of your Thesis Management System and the core technologies you chose.

**You:**  
The entire application follows a classic **MVC-like pattern** built on **Flask** (a lightweight Python micro-framework).  

- **Model layer** → MySQL relational database (normalized EER → schema).  
- **View layer** → HTML + Jinja2 templates (client-side rendering).  
- **Controller layer** → Flask routes + session management.  

**Broad theory:** Flask is deliberately minimal; it gives you the freedom to implement your own routing, ORM (we used raw SQL with `cursor` for full control), and security. This is perfect for an academic project because you see exactly how every HTTP request maps to database operations, file I/O, and template rendering.

**Key stack:**
- Backend: Flask + MySQL + bcrypt + Werkzeug (secure_filename)
- Frontend: Pure HTML + Jinja2 (no heavy JS frameworks)
- Session: Flask’s built-in `session` with a secret key
- File storage: Local `/uploads` folder (production would be S3)
- Password hashing: bcrypt (never plain text)

---

**Interviewer:** Let’s go feature-by-feature. How does **Admin Access** actually work end-to-end?

**You:**  
1. **Login flow**  
   - User selects “admin” role on `/login`.  
   - Flask route does `SELECT pass FROM Admin WHERE id = %s`.  
   - `bcrypt.checkpw(plain_password, hashed_password)` validates.  
   - If OK → `session['user_id'] = id; session['role'] = 'admin'`.

2. **Authorization middleware**  
   Every admin-only route starts with:  
   ```python
   if 'role' not in session or session['role'] != 'admin':
       return redirect(url_for('login_page'))
   ```

3. **Edit Password**  
   - Admin dashboard loads all users via a UNION view or separate JOINs.  
   - Clicking “Edit Password” → POST to `/edit_password/<user_id>`.  
   - Backend determines the correct password table (`StudentPass`, `FacultyPass`, or `Admin`) and does `UPDATE ... SET pass = %s` with newly hashed value.

**Broad theory:** This is classic **Role-Based Access Control (RBAC)**. Sessions act as the stateless-to-stateful bridge in a server-rendered app. Using separate password tables demonstrates the **Single Responsibility Principle** – one table never holds another user’s credentials.

---

**Interviewer:** How does **Profile Editing + Multi-valued attributes** (interests, links, consultation hours) work?

**You:**  
- Core entity tables (`Student`, `Faculty`) store atomic fields.  
- Multi-valued attributes are normalized into **junction tables** (1:M):  
  - `StudentInterests(stu_id, interest)`  
  - `FacultyLinks(fac_id, link)`  
  - `FacultyConsultationHrs(fac_id, con_hrs)`

**Edit flow (example: student):**
1. GET `/edit_student_profile/<id>` → fetch current data + lists from junction tables.  
2. User submits form (multiple inputs for interests/links).  
3. Backend:  
   - `DELETE FROM StudentInterests WHERE stu_id = %s` (clear old)  
   - Loop over form arrays → `INSERT` new rows  
   - All inside a transaction (`conn.commit()`)

**Broad theory:** This is **database normalization in action** (we proved 1NF/2NF/3NF in the report). It eliminates repeating groups and partial/transitive dependencies. Jinja2 loops render dynamic lists on the frontend, keeping the UI clean.

---

**Interviewer:** Explain **Group Formation** – how does a student create a group and invite peers?

**You:**  
- `/create_group` (POST) → `INSERT INTO Group(...)` with `student_count = 1`, then updates creator’s `group_id` in `Student` table.  
- Search peers via `/search_groups` or `/search_students` (Jinja2-powered tables).  
- Join requests use a pending table (or `RegSupervisor` style junction).  
- Leader approves → increment `student_count`, add to group members (via junction if needed), delete pending rows.

**Broad theory:** This implements a **many-to-many relationship with state** (pending → approved). Foreign keys + triggers (or explicit route logic) maintain referential integrity and the “once approved, reject others” business rule.

---

**Interviewer:** Supervisor Selection & Slot Booking – how do these two features interact?

**You:**  
**Supervisor Selection:**
- Student group browses `/search_faculties` (filtered by interests + `slot_available`).  
- POST `/request_supervisor/<group_id>/<fac_id>` → insert into `RegSupervisor(group_id, sup_id, status='pending')`.  
- Faculty views `/faculty_supervision_requests` → accept/reject.  
- On accept:  
  - `UPDATE Group SET sup_id = %s`  
  - Auto-reject other pending requests for same group (`UPDATE ... SET status='rejected' WHERE group_id = %s AND sup_id != %s`)

**Slot Booking (Meet table):**
- Faculty profile shows `FacultyConsultationHrs` + available `Meet` slots.  
- Student books → status changes `available → requested`.  
- Faculty confirms → `confirmed` and auto-rejects overlapping slots (SQL `OVERLAPS` or time-range check).

**Broad theory:** This is **workflow state management** with composite primary keys (`group_id + fac_id + date_time`). The automatic cleanup demonstrates **event-driven consistency** – one action (approval) triggers multiple DB updates to keep the system in a valid business state.

---

**Interviewer:** File Submission + Feedback System – how is the threaded conversation implemented?

**You:**  
Two tables:
- `GroupFile(id, group_id, reply_file_id, subject, remarks, file_link, date)`
- `FacultyFile(id, fac_id, subject, remarks, file_link, date)`

**Flow:**
1. Student uploads thesis/gradesheet → `reply_file_id = NULL`.  
2. Supervisor replies → insert into `FacultyFile`, then update the original `GroupFile` row with `reply_file_id = LAST_INSERT_ID()`.  
3. `/group_inbox/<group_id>` does two queries:  
   - Main faculty files (`reply_file_id IS NULL`)  
   - Student replies (`WHERE reply_file_id = parent_id`)  
   - Ordered by `date DESC`.

**Broad theory:** This is a **self-referential (adjacency list) pattern** for threaded comments. Werkzeug’s `secure_filename` + `send_from_directory` handles secure file serving. MIME-type checks enforce PDF/LaTeX only.

---

**Interviewer:** Security & Performance – what did you focus on?

**You:**  
- **Passwords:** bcrypt (slow, salted hash – resists brute-force).  
- **Sessions:** Signed cookies + secret key.  
- **Authorization:** Checked on every sensitive route.  
- **File uploads:** `secure_filename`, size/type validation, local folder (production → cloud storage).  
- **SQL safety:** Parameterized queries (`%s` placeholders) – no raw string concatenation.

**Broad theory:** We applied the **OWASP top-10 principles** at a basic level (injection prevention, broken auth, insecure file upload). Normalization + proper indexing (PK/FK) keeps queries fast even when joining many tables.

---

**Interviewer:** Any broad architectural theories you applied?

**You:**  
1. **Separation of Concerns** – frontend (Jinja2) only renders; backend does all business logic.  
2. **Normalization vs Denormalization** – we stayed fully normalized for data integrity (report proves 3NF).  
3. **Stateless HTTP + Server-side Sessions** – classic web pattern before SPAs.  
4. **Event-driven consistency** – approval of supervisor automatically cleans pending requests.  
5. **Progressive enhancement** – everything works with plain HTML; Jinja2 makes it dynamic.

**Interviewer:** Final thoughts?

**You:**  
The project is a complete end-to-end demonstration of relational database design, Flask routing patterns, secure file handling, and role-based workflows. Every feature is traceable from ER diagram → normalized schema → Flask route → Jinja2 template. It’s a perfect example of how a lightweight stack can power a real academic process.

---

**End of Technical Interview Document**  
(Ready to copy-paste as `Thesis_Management_System_Technical_Interview.md`)