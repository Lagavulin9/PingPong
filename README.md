# Devcontainer for vSomeIP/CommonAPI
This project aims to provide an environment for developing vsomeip applications.
Provided dockerfile will prepare all the dependencies for vsomeip library libraries.
Simple Ping-Pong example is also included in the repository. So take a look if you don't know what to do! 

# How to use
1. Install [VSCode](https://code.visualstudio.com/)
2. Install `Dev Containers` extension.
3. Open command palette and select `Open folder in container`
4. Wait for docker image to be built.
5. You can now work on container with all the dependencies. Have fun!

# Recommended structure
```
├── conf
│   ├──  *.json
├── include
│   └──  *.hpp
├── src
│   └──  *.cpp
└── CMakeLists.txt
```

# CI-CD
In progress.

# See also
[vsomeip in 10 minutes](https://github.com/COVESA/vsomeip/wiki/vsomeip-in-10-minutes)<br>
[Developing inside a Container](https://code.visualstudio.com/docs/devcontainers/containers)<br>
[Understanding GitHub Actions](https://docs.github.com/en/actions/learn-github-actions/understanding-github-actions)
