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

### Install Requirements:

```shell
sudo chmod 777 setup.sh
./setup.sh
```

### Run the Engine in Desktop Release or Desktop Editor mode
- Open 'DeepsEngine' folder in CLion
  - Enable autoreload for CMake changes
  - Go to Preferences -> Build, Execution, Deployment -> CMake and add the following profiles:
    - Release
      - In "Environment" add "WITH_EDITOR="
    - Editor
      - Nothing in "Environment"
      - Add the following compile options
        - "-DCMAKE_PREFIX_PATH=/opt/homebrew/Cellar/qt@5/5.15.3"
- Run the CMake application in either Editor or Release mode (if you encounter errors, you might have to reload the CMake profiles)

### Run the Web Release of the Engine

```shell
sudo chmod -R 777 web_build
cd web_build
./build.sh
```

## Troubleshooting (Development)

If you are receiving errors while installing new vcpkg packages, please delete the vcpkg folder in root and reinstall everything.

```shell
sudo chmod 777 setup.sh
rm -rf vcpkg
./setup.sh
```