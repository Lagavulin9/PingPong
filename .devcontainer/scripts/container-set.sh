# Create remote user
useradd vscode -m
echo 'vscode:vscode' | chpasswd
usermod -aG sudo vscode

# Create a symbolic link for .ini
if [ -f "conf/commonapi.ini" ]; then
	ln -s "$(pwd)/conf/commonapi.ini" /etc/commonapi.ini
    echo "Symbolic link for commonapi.ini created successfully."
else
    echo "commonapi.ini does not exist."
fi