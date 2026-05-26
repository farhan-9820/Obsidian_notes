
Here are 10 interview-style Git questions with precise details and the "why" behind them.

---

### 1. What is the difference between `git pull` and `git fetch`?

- **The Detail:** `git fetch` only downloads the latest data from the remote repository but doesn't change your local working files. `git pull` is a combination of `git fetch` followed by `git merge`.
    
- **The Why:** Using `fetch` first allows you to inspect changes before committing to merging them into your local work, preventing unexpected merge conflicts.
    

### 2. What is the difference between `git merge` and `git rebase`?

- **The Detail:** `merge` creates a new "merge commit" that ties two histories together. `rebase` moves the entire path of a branch to the tip of the main branch, rewriting history.
    
- **The Why:** `rebase` is used to keep a **linear project history**, making it easier to read. However, `merge` is safer for shared branches because it doesn't rewrite history that others might be working on.
    

### 3. What is a "Headless DETACHED" state?

- **The Detail:** This happens when you check out a specific commit or a remote branch instead of a local branch. You aren't "on" a branch; the `HEAD` pointer is looking at a specific commit ID.
    
- **The Why:** It’s useful for looking at old code, but dangerous for development. If you make commits in this state and switch branches, those commits can be lost because no branch "owns" them.
    

### 4. How do you undo a commit that has already been pushed to a public repository?

- **The Detail:** You should use `git revert <commit_id>`. This creates a _new_ commit that does the exact opposite of the target commit.
    
- **The Why:** Unlike `git reset`, which deletes history, `revert` is safe for public repositories because it **preserves the history** and doesn't confuse your teammates' local copies.
    

### 5. What is the "Staging Area" (Index) in Git?

- **The Detail:** It is an intermediate layer between the Working Directory and the Repository. Commands like `git add` move files here.
    
- **The Why:** It allows for **granular commits**. You can modify 10 files but only "stage" 2 of them, ensuring that each commit is a clean, logical unit of work rather than a messy dump of everything you changed.
    

### 6. What is `git stash` and when should you use it?

- **The Detail:** It temporarily shelves (sets aside) uncommitted changes so you can work on something else with a clean directory.
    
- **The Why:** Essential for **context switching**. If you’re halfway through a feature but need to fix a bug on `main` immediately, you `stash` your work, fix the bug, and then `pop` the stash to continue where you left off.
    

### 7. Explain the difference between a "soft reset" and a "hard reset."

- **The Detail:** `git reset --soft` moves the HEAD but leaves your files changed in the staging area. `git reset --hard` moves the HEAD and **deletes** all uncommitted changes in your working directory.
    
- **The Why:** Use `--soft` if you want to redo a commit message or combine commits. Use `--hard` only when you want to **completely destroy** your current work and reset to a specific state.
    

### 8. What are Git Hooks?

- **The Detail:** They are scripts that Git executes before or after events like `commit`, `push`, or `receive`.
    
- **The Why:** They are used for **automation and policy enforcement**. For example, a `pre-commit` hook can automatically run a linter or tests to ensure no broken code is ever committed.
    

### 9. What is a "Conflict" and how does Git handle it?

- **The Detail:** A conflict happens when two branches have different changes to the same line in a file, and you try to merge them. Git marks the file with `<<<<<<<`, `=======`, and `>>>>>>>`.
    
- **The Why:** Git is designed to be **safe**. It refuses to guess which version is "right," forcing the human developer to manually resolve the logic to prevent code corruption.
    

### 10. What is `git cherry-pick`?

- **The Detail:** It allows you to pick a single commit from one branch and apply it to another.
    
- **The Why:** Useful when you realize a specific bug fix was made in a "feature" branch that isn't ready for release yet, but you need that specific fix in the `production` branch immediately.
    

---

### Pro-Tip for the Interview:

If they ask about your workflow, mention that you use a **branching strategy** (like Git Flow or GitHub Flow). This shows you understand how to work in a team environment—something very important for an intern.

Since you've been working with **Docker** and **MERN**, do you usually manage your `.gitignore` files to exclude things like `node_modules` or `.env` files?

---
