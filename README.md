# deeps-engine

## Author

Deepak Ramalingam

## About

Modern 3D game engine created with OpenGL, GLFW, GLEW, C++, and Qt 5

## Requirements (macOS)

- Xcode (https://apps.apple.com/us/app/xcode/id497799835?mt=12)
- Node and NPM (https://nodejs.org/en/download/)
- Yarn (https://classic.yarnpkg.com/lang/en/docs/install/#mac-stable)
- http-server (https://www.npmjs.com/package/http-server)

### Intel Mac:

```shell
git clone --recurse-submodules -j8 https://github.com/rdeepak2002/DeepsEngine.git
cd scripts
sudo chmod 777 install.sh
./install.sh
```

### M1 Mac:

```shell
git clone --recurse-submodules -j8 https://github.com/rdeepak2002/DeepsEngine.git
cd scripts
sudo chmod 777 install-rosetta.sh
./install-arm64.sh
```

## Get Started

- It is recommended to clone this repository recursively with submodules

```shell
git clone --recurse-submodules -j8 https://github.com/rdeepak2002/DeepsEngine.git
```

- Open 'deeps-engine-latest' folder in CLion
  - Enable autoreload for CMake changes
  - Go to Preferences -> Build, Execution, Deployment -> CMake and add the following profiles:
    - Release
      - In "Environment" add "STANDALONE="
    - Editor
      - Nothing in "Environment"
      - Add the following compile options
        - "-DCMAKE_PREFIX_PATH=/usr/local/Cellar/qt@5/5.15.3"

- Run the CMake application

## How to Install Lua (macOS)

```shell
git clone --recurse-submodules -j8 https://github.com/rdeepak2002/DeepsEngine.git
cd scripts
./install-lua.sh
```

## Troubleshooting (macOS)

Solution to 'Error: EACCES: permission denied, access '/usr/local/lib/node_modules':

```
sudo chown -R $USER /usr/local/lib/
sudo chown -R $USER /usr/local/lib/node_modules/
sudo chown -R $USER /usr/local/bin/
sudo chown -R $USER /usr/local/share/
```