# deeps-engine

## Author
Deepak Ramalingam

## About
2D and 3D game engine using OpenGL, GLFW, GLEW, C++, Node, Node-API, React, Electron, and Typescript.

## Requirements (macOS)

- Xcode (https://apps.apple.com/us/app/xcode/id497799835?mt=12)
  - create an arbitrary blank project and build it to ensure everything is working properly
- Homebrew (https://brew.sh/)
- Node and NPM (https://nodejs.org/en/download/)
- Yarn (https://classic.yarnpkg.com/lang/en/docs/install/#mac-stable)
- Glad
  - generate zip file from https://glad.dav1d.de/ (gl: 'Version 3.3', profile: 'Core', 'Generate a loader' ticked)
    - Permalink: https://glad.dav1d.de/#language=c&specification=gl&api=gl%3D3.3&api=gles1%3Dnone&api=gles2%3Dnone&api=glsc2%3Dnone&profile=core&loader=on
  - extract zip, then move 'glad' and 'KHR' folders (located in 'include' folder) to '/usr/local/include'
  - change line 89 of 'glad.h' (located in /usr/local/include/glad) from '#include <KHR/khrplatform.h>' to '#include <khrplatform.h>'
- CMake (refer to below commands)
- GLFW (refer to below commands)
  - change lines 12 and 20 (GLFW paths) of CMakeLists.txt if necessary
- GLEW (refer to below commands)
  - change lines 11 and 19 (GLEW paths) of CMakeLists.txt if necessary
- OpenCV (refer to below commands)

```
brew install cmake
brew install glfw3
brew install glew
brew install opencv
```

## Get Started (macOS)

```
cd editor
yarn
yarn start
```

## Recommended Development Environment

- Open 'engine' folder in CLion
  - Enable autoreload for CMake changes
- Open 'editor' folder in WebStorm
