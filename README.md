# deeps-engine

## Author
Deepak Ramalingam

## About
Modern 3D game engine created with OpenGL, GLFW, GLEW, C++, and Qt 5

## Requirements (macOS)

- Xcode (https://apps.apple.com/us/app/xcode/id497799835?mt=12)
  - create an arbitrary blank project and build it to ensure everything is working properly
- Homebrew (https://brew.sh/)
- Node and NPM (https://nodejs.org/en/download/)
- Yarn (https://classic.yarnpkg.com/lang/en/docs/install/#mac-stable)
  - refer to 'Node / NPM Troubleshooting (macOS)' section below
- Glad
  - generate zip file from https://glad.dav1d.de/ (gl: 'Version 3.3', profile: 'Core', 'Generate a loader' ticked)
    - Permalink: https://glad.dav1d.de/#language=c&specification=gl&api=gl%3D3.3&api=gles1%3Dnone&api=gles2%3Dnone&api=glsc2%3Dnone&profile=core&loader=on
  - extract zip, then move 'glad' and 'KHR' folders (located in 'include' folder) to '/usr/local/include'
  - change line 89 of 'glad.h' (located in /usr/local/include/glad) from '#include <KHR/khrplatform.h>' to '#include <khrplatform.h>'
- CMake (refer to below commands)
- GLFW (refer to below commands)
- GLEW (refer to below commands)
- OpenCV (refer to below commands)
- http-server (https://www.npmjs.com/package/http-server)
- SDL2 (https://www.libsdl.org/download-2.0.php)
- Lua (refer to below commands)

Intel Mac:

```
brew install cmake
brew install glfw3
brew install glew
brew install glm
brew install rapidjson
brew install qt@5
brew install skypjack/entt/entt
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
arch -x86_64 /usr/local/bin/brew install rapidjson
arch -x86_64 /usr/local/bin/brew install qt@5
arch -x86_64 /usr/local/bin/brew install skypjack/entt/entt
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
