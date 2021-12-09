# deeps-engine

## Author
Deepak Ramalingam

## About
2D and 3D game engine using OpenGL, GLFW, GLEW, C++, Node, Node-API, React, Electron, and Typescript.

## Requirements (macOS)

- Xcode (https://apps.apple.com/us/app/xcode/id497799835?mt=12)
- Homebrew (https://brew.sh/)
- Node and NPM (https://nodejs.org/en/download/)
- Yarn (https://classic.yarnpkg.com/lang/en/docs/install/#mac-stable)
- Glad
  - generate zip file from https://glad.dav1d.de/ (gl: 'Version 3.3', profile: 'Core', 'Generate a loader' ticked)
    - Permalink: https://glad.dav1d.de/#language=c&specification=gl&api=gl%3D3.3&api=gles1%3Dnone&api=gles2%3Dnone&api=glsc2%3Dnone&profile=core&loader=on
  - extract zip, then move 'glad' and 'KHR' folders (located in 'include' folder) to '/usr/local/include'
- CMake (refer to below commands)
- GLFW (refer to below commands)
- GLEW (refer to below commands)
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
