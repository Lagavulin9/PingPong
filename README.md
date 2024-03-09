# Devcontainer for vSomeIP/CommonAPI
This project aims to provide an environment for developing vsomeip applications or CommonAPI applications. Provided dockerfile will prepare all the dependencies for vsomeip library and also CommonAPI, CommonAPI-SomeIP libraries. Simple Ping-Pong example is also included in the repository. So take a look if you don't know what to do! 

# How to use
1. Install [VSCode](https://code.visualstudio.com/)
2. Install `Dev Containers` extension.
3. Open command palette and select `Open folder in container`
4. Wait for docker image to be built.
5. You can now work on container with all the dependencies. Have fun!

# Recommended structure
```
├── fidl
│   ├──  *.fdepl
│   └──  *.fidl
├── include
│   └──  *.hpp
├── src
│   └──  *.cpp
├── src-gen
│   ├──  core
│   │    └── Files from core-generator
│   └──  someip
│        └── Files from someip-generator
└── CMakeLists.txt
```

# CI-CD
If you are developing CommonAPI applications you will need to use code generators to create source codes for IPC binding. I also added Github Action workflow in the repository so that whenever `.fidl` or `.fdepl` is modified and pushed to the repo, it will automatically update generated code in `src-gen`. And I think this is also useful when you are working on arm devices since code generator only works on x86(_64) processors.

> If you are already working on x86(_64) processors and want to generate code rightaway in devcontainer binaries are already installed in the container. You can use them in terminal like below.<br> `commonapi-core-generator-{YOUR SYSTEM}` for `.fidl` files and<br> `commonapi-someip-generator-{YOUR SYSTEM}` for `.fdepl` files.

# See also
[vsomeip in 10 minutes](https://github.com/COVESA/vsomeip/wiki/vsomeip-in-10-minutes)<br>
[CommonAPI wiki](https://github.com/COVESA/capicxx-core-tools/wiki)<br>
[Developing inside a Container](https://code.visualstudio.com/docs/devcontainers/containers)<br>
[Understanding GitHub Actions](https://docs.github.com/en/actions/learn-github-actions/understanding-github-actions)