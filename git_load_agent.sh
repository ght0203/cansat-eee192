#!/bin/bash

# This script is run when using a new machine for git authentication setup
# Some useful commands below: 
# eval "$(ssh-agent -s)"
# ssh-add ~/.ssh/id_ed25519
# git remote -v
# git config --global core.sshCommand "ssh -i ~/.ssh/id_ed25519"


# Prompt for GitHub username and email
read -p "Enter your GitHub username: " GITHUB_USER
read -p "Enter your GitHub email: " GITHUB_EMAIL

# Configure Git username and email
git config --global user.name "$GITHUB_USER"
git config --global user.email "$GITHUB_EMAIL"

# Ensure SSH directory exists
mkdir -p ~/.ssh
chmod 700 ~/.ssh

# Define SSH key file
SSH_KEY=~/.ssh/id_ed25519

# Generate a new SSH key if it doesn't exist
if [ ! -f "$SSH_KEY" ]; then
    echo "Generating a new SSH key..."
    ssh-keygen -t ed25519 -C "$GITHUB_EMAIL" -f "$SSH_KEY" -N ""
else
    echo "SSH key already exists."
fi

# Ensure SSH agent is running
eval "$(ssh-agent -s)"

# Add the SSH key to the agent
ssh-add "$SSH_KEY"

# Set up SSH config for GitHub
SSH_CONFIG=~/.ssh/config
if ! grep -q "Host github.com" "$SSH_CONFIG"; then
    echo "Setting up SSH config for GitHub..."
    cat >> "$SSH_CONFIG" <<EOL

Host github.com
    User git
    IdentityFile ~/.ssh/id_ed25519
    AddKeysToAgent yes
EOL
    chmod 600 "$SSH_CONFIG"
fi

# Display the SSH public key for easy GitHub setup
echo -e "\n📌 Copy the following SSH key and add it to your GitHub account:"
cat "$SSH_KEY.pub"
echo -e "\n🔗 Go to: https://github.com/settings/keys and click 'New SSH Key'."
echo "Press ENTER after you've added the key..."
read -r  # Wait for user confirmation

# Test SSH connection
echo "🔄 Testing SSH connection..."
ssh -T git@github.com

echo "✅ Git and SSH setup complete!"


