# Create remote user
useradd vscode -m
echo 'vscode:vscode' | chpasswd
usermod -aG sudo vscode