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

Install Emscripten

```shell
brew install emscripten
```

Update lua-web Build

```shell
cd src/engine/lib
sudo chmod 777 download-lua-web.sh
./download-lua-web.sh
```

Create the Web Build and Serve It

```shell
sudo chmod -R 777 web_build
cd web_build
./build.sh
```