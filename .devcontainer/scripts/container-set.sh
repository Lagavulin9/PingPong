echo "#######################################################"
echo "### Checking container creation                     ###"
echo "#######################################################"
useradd vscode --password vscode -m
usermod -aG sudo vscode