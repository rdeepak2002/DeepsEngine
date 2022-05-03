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

### Install Requirements on Mac:

```shell
cd scripts
sudo chmod 777 install.sh
./install.sh
```

### Run the Engine in Desktop Release or Desktop Editor mode
- Open 'deeps-engine-latest' folder in CLion
  - Enable autoreload for CMake changes
  - Go to Preferences -> Build, Execution, Deployment -> CMake and add the following profiles:
    - Release
      - In "Environment" add "STANDALONE="
    - Editor
      - Nothing in "Environment"
      - Add the following compile options
        - "-DCMAKE_PREFIX_PATH=/opt/homebrew/Cellar/qt@5/5.15.3"
- Run the CMake application in either Editor or Release mode

### Run the Web Release of the Engine on macOS

```shell
cd web_build
sudo chmod 777 build.sh
./build.sh
```
