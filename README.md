# deeps-engine

## Author
Deepak Ramalingam

## About
Modern 3D game engine created with OpenGL, GLFW, GLEW, C++, and Qt 5

## Clone with Submodules

It is recommended to clone this repository with submodules

```shell
git clone --recurse-submodules -j8 https://github.com/rdeepak2002/DeepsEngine.git
```

## Requirements (macOS)

- Xcode (https://apps.apple.com/us/app/xcode/id497799835?mt=12)
  - create an arbitrary blank project and build it to ensure everything is working properly
- Homebrew (https://brew.sh/)
- Node and NPM (https://nodejs.org/en/download/)
- Yarn (https://classic.yarnpkg.com/lang/en/docs/install/#mac-stable)
  - refer to 'Node / NPM Troubleshooting (macOS)' section below
- CMake (refer to below commands)
- GLFW (refer to below commands)
- GLEW (refer to below commands)
- http-server (https://www.npmjs.com/package/http-server)
- Lua (refer to below commands)

Intel Mac:

```
brew install cmake
brew install glfw3
brew install glew
brew install glm
brew install qt@5
brew install lua
brew install lua@5.3
```

Refer to instructions below for M1 Mac

## Requirements M1 Mac (using Rosetta)

Open terminal using Rosetta

Install brew

```
arch -x86_64 zsh  
arch -x86_64 /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install.sh)"
```

Install clang

```
arch -x86_64 /usr/local/bin/brew install llvm
```

Install other dependencies

```
arch -x86_64 /usr/local/bin/brew install cmake
arch -x86_64 /usr/local/bin/brew install glfw3
arch -x86_64 /usr/local/bin/brew install glew
arch -x86_64 /usr/local/bin/brew install glm
arch -x86_64 /usr/local/bin/brew install qt@5
arch -x86_64 /usr/local/bin/brew install lua
arch -x86_64 /usr/local/bin/brew install lua@5.3
```

## Get Started

- Add the following compile options for CLion

```shell
-DCMAKE_PREFIX_PATH=/usr/local/Cellar/qt@5/5.15.2_1
```

- Open 'deeps-engine-latest' folder in CLion
  - Enable autoreload for CMake changes
  - Recommended plugin for GLSL: https://plugins.jetbrains.com/plugin/6993-glsl-support
  - Go to Preferences -> Build, Execution, Deployment -> CMake and add a profile:
    - Release
      - In "Environment" add "STANDALONE="

- Run the CMake application

## How to Build Lua for Emscripten / Web Assembly

Run the following command in the deeps-engine-latest/src/engine/external/lua-5.3.6/src folder:

```shell
make generic CC='emcc -s WASM=1' AR='emar rcu' RANLIB='emranlib'
```

Link as library for emscripten (step already done, just rewriting it here for future readers to understand):

```cmake
if (${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
  set_target_properties(Release PROPERTIES LINK_FLAGS "... -L${PROJECT_SOURCE_DIR}/src/engine/external/lua-5.3.6/src -s ...")
endif ()
```

## How to Install QT

Install qt on macOS:
```shell
arch -x86_64 /usr/local/bin/brew install qt@5
```

Compile options for CLion:
```shell
-DCMAKE_PREFIX_PATH=/usr/local/Cellar/qt@5/5.15.2_1
```
