eval "$(ssh-agent -s)"
ssh-add ~/.ssh/id_ed25519
git remote -v
# git config --global core.sshCommand "ssh -i ~/.ssh/id_ed25519"

