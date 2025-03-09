# cansat-eee192
# Git Best Practices

This guide provides beginner-friendly best practices for using Git commands such as `push`, `pull`, `commit`, `revert`, and more. Following these guidelines will help keep your repository clean and organized.

---

## 📌 **Committing Changes**

### ✅ Best Practices:
- Commit **small, logical changes** instead of large commits.
- Use **clear and descriptive commit messages** (e.g., `fix: correct typo in README`).
- Check your changes with `git status` before committing.

### 🔹 Commands:
```sh
git add <file>       # Stage a specific file
git add .            # Stage all modified and new files
git commit -m "Add login validation"
git commit -am "Fix typo in README"  # Add and commit in one step
```

---

## 🔄 **Pulling Changes**

### ✅ Best Practices:
- **Always pull before pushing** to avoid conflicts.
- Use `git fetch` to check for changes before merging.

### 🔹 Commands:
```sh
git fetch            # Get the latest changes without merging
git pull             # Fetch and merge remote changes
```

---

## 🚀 **Pushing Changes**

### ✅ Best Practices:
- Only push changes **after pulling the latest updates**.
- Use **feature branches** instead of pushing directly to `main`.

### 🔹 Commands:
```sh
git push origin <branch>   # Push branch to remote repository
```

---

## 🔁 **Undoing Changes**

### ✅ Best Practices:
- Use `git revert` to safely undo a commit (creates a new commit to undo changes).
- Use `git reset` to undo local changes before pushing.
- Use `git restore` to discard changes in a file.

### 🔹 Commands:
```sh
git revert <commit>         # Revert a commit safely
git reset HEAD <file>       # Unstage a file (undo git add)
git reset --soft HEAD~1     # Undo last commit but keep changes staged
git reset --hard HEAD~1     # Undo last commit and discard changes
git restore <file>          # Discard local file changes
```

---

## 🌳 **Branching Best Practices**

### ✅ Best Practices:
- Use **feature branches** for new work (e.g., `feat-login-page`).
- Keep `main` stable by merging only completed branches.

### 🔹 Commands:
```sh
git branch <branch-name>      # Create a new branch
git switch <branch-name>      # Switch to a branch
git merge <branch-name>       # Merge another branch into current
git branch -d <branch-name>   # Delete a local branch
```

---

## 🛠 **Resolving Merge Conflicts**

### ✅ Best Practices:
- Use `git status` to see conflicting files.
- Edit conflicting files manually, then run `git add` and `git commit`.

### 🔹 Commands:
```sh
git merge <branch>           # Merge a branch
git status                   # Check for conflicts
git add <conflicted-file>    # Mark conflict as resolved
git commit                   # Complete the merge
```

---

## 🎯 **Other Useful Commands**
```sh
git log --oneline --graph    # View commit history compactly
git stash                    # Save uncommitted changes temporarily
git stash pop                # Restore stashed changes
```

By following these best practices, you can ensure a smooth workflow and avoid common Git mistakes! 🚀