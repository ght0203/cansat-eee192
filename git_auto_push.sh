#!/bin/bash

# Define commit message
COMMIT_MSG="update x"

# Add all changes
git add .

# Commit with the predefined message
git commit -m "$COMMIT_MSG"

# Push to the main branch
git push origin main

# Confirmation message
echo "✅ Changes pushed successfully!"

