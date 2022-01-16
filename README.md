# deeps-engine

## Author
Deepak Ramalingam

## About
3D game engine using OpenGL, GLFW, GLEW, C++, Node-API, NodeGui, React, and Typescript

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

Intel Mac:

```
brew install cmake
brew install glfw3
brew install glew
brew install glm
brew install rapidjson
brew install qt@5
```

export QT_INSTALL_DIR=/usr/local/Cellar/qt@5/x.x.x

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
```

export QT_INSTALL_DIR=/usr/local/Cellar/qt@5/x.x.x

## Get Started (macOS)

Intel Mac:

```
git clone https://github.com/rdeepak2002/deeps-engine.git
cd deeps-engine/deeps-engine-latest

# install dependencies
yarn
# run the dev server
yarn dev
# open another terminal and run the app
yarn start
```

M1 Mac (using Rosetta):

```
git clone https://github.com/rdeepak2002/deeps-engine.git
cd deeps-engine/deeps-engine-latest

# install dependencies
arch -x86_64 yarn
# run the dev server
arch -x86_64 yarn dev
# open another terminal and run the app
arch -x86_64 yarn start
```

## Node / NPM Troubleshooting (macOS)

Solution for 'Error: EACCES: permission denied, access '/usr/local/lib/node_modules':

```
sudo chown -R $USER /usr/local/lib/
sudo chown -R $USER /usr/local/lib/node_modules/
sudo chown -R $USER /usr/local/bin/
sudo chown -R $USER /usr/local/share/
```

## Recommended Development Environment

- Open 'deeps-engine-latest' folder in CLion
  - Enable autoreload for CMake changes
  - Recommended plugin for GLSL: https://plugins.jetbrains.com/plugin/6993-glsl-support
  - Go to Preferences -> Build, Execution, Deployment -> CMake and add a profile:
    - Release
      - In "Environment" add "STANDALONE="
