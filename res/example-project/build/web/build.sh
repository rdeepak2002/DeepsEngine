#!/bin/sh

# allow modification of this folder
sudo chmod -R 777 ./

echo ${DEEPS_ENGINE_RESOURCE_DIRECTORY}

if [[ -z "${DEEPS_ENGINE_RESOURCE_DIRECTORY}" ]]; then
  echo "Error: DEEPS_ENGINE_RESOURCE_DIRECTORY env variable not provided!"
  exit 1
else
  echo "Resource directory set to ${DEEPS_ENGINE_RESOURCE_DIRECTORY}"
fi

if [ -d "DeepsEngine" ]; then
  echo "DeepsEngine already built..."
else
  echo "Building DeepsEngine..."
  ./build-library.sh
fi

# download emscripten
./download-emscripten.sh
source emsdk/emsdk_env.sh

# download assimp for web
if [ -d "assimp-5.0.1" ]; then
  echo "Assimp already built..."
else
  echo "Building Assimp..."
  ./download-assimp.sh
fi

source emsdk/emsdk_env.sh

# install vcpkg stuff
rm -rf vcpkg
./download-vcpkg.sh
export VCPKG_ROOT="$(pwd)/vcpkg"
./vcpkg/vcpkg install lua:wasm32-emscripten
./vcpkg/vcpkg install yaml-cpp:wasm32-emscripten
#./vcpkg/vcpkg install assimp:wasm32-emscripten

echo "Creating web build..."

# remove current source code
rm -rf build

# create new folder for source code
mkdir -p build/assets/project/src
cp app.html build/app.html
cp firebase.json build/firebase.json
cp -R ${DEEPS_ENGINE_RESOURCE_DIRECTORY} build/assets/project

# build source code
cmake -S ./ -B build "-DVCPKG_CHAINLOAD_TOOLCHAIN_FILE=$(pwd)/emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake" "-DCMAKE_TOOLCHAIN_FILE=$(pwd)/vcpkg/scripts/buildsystems/vcpkg.cmake" "-DVCPKG_TARGET_TRIPLET=wasm32-emscripten"
cmake --build build

echo "Build complete and present in $(pwd)/build/"

# serve content
if [[ "${DEEPS_ENGINE_WEB_SERVE_CONTENT_DETACHED}" == true ]]; then
  pkill http-server
  echo "Serving content detached from /build/app.html"
  http-server -o "/build/app.html" --silent &
fi

if [[ "${DEEPS_ENGINE_WEB_SERVE_CONTENT}" == true ]]; then
  pkill http-server
  echo "Serving content attached from /build/app.html"
  http-server -o "/build/app.html" --silent
fi

exit 0