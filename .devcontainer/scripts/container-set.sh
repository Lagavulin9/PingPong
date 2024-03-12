echo "#######################################################"
echo "### Checking container creation                     ###"
echo "#######################################################"
useradd vscode -m
echo 'vscode:vscode' | chpasswd
usermod -aG sudo vscode