# deeps-engine

## Author

Deepak Ramalingam

## About

Modern 3D game engine created with OpenGL, GLFW, GLEW, C++, and Qt 5

## Get Started (Development)

- It is recommended to clone this repository recursively with submodules

```shell
git clone --recurse-submodules -j8 https://github.com/rdeepak2002/DeepsEngine.git
```

### Install Requirements on Intel Mac:

```shell
cd scripts
sudo chmod 777 install.sh
./install.sh
```

### Install Requirements on M1 Mac:

```shell
cd scripts
sudo chmod 777 install-rosetta.sh
./install-arm64.sh
```

### Run the engine in Release or Editor mode
- Open 'deeps-engine-latest' folder in CLion
  - Enable autoreload for CMake changes
  - Go to Preferences -> Build, Execution, Deployment -> CMake and add the following profiles:
    - Release
      - In "Environment" add "STANDALONE="
    - Editor
      - Nothing in "Environment"
      - Add the following compile options
        - "-DCMAKE_PREFIX_PATH=/usr/local/Cellar/qt@5/5.15.3"
- Run the CMake application in either Editor or Release mode

### Run the engine on the web
```shell
cd web_build
sudo chmod 777 build.sh
./build.sh
```
