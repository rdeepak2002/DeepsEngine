#!/bin/sh

# allow modification of this folder
sudo chmod -R 777 ./

rm -rf web-library

# download emscripten
if [ -d "emsdk" ]; then
  echo "emsdk already downloaded..."
else
  echo "Downloading emsdk..."
  ./download-emscripten.sh
fi
source emsdk/emsdk_env.sh

# download assimp for web
if [ -d "assimp-5.0.1" ]; then
  echo "Assimp already built..."
else
  echo "Building Assimp..."
  ./download-assimp.sh
fi

source emsdk/emsdk_env.sh

# download and build lua
if [ -d "lua-5.4.4" ]; then
  echo "Lua already built..."
else
  echo "Building Lua..."
  ./download-lua.sh
fi

source emsdk/emsdk_env.sh

# download and build yaml-cpp
if [ -d "yaml-cpp" ]; then
  echo "YAML-CPP already built..."
else
  echo "Building YAML-CPP..."
  ./download-yaml-cpp.sh
fi

source emsdk/emsdk_env.sh

echo "Creating web library..."

# remove current library code
rm -rf web-library

# build source code
export AS_LIBRARY=""
cmake -S ../../../.. -B web-library "-DCMAKE_TOOLCHAIN_FILE=$(pwd)/emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake" -DCMAKE_POSITION_INDEPENDENT_CODE=ON
cmake --build web-library

# copy compiled library to engine lib folder
mkdir -p ../../../../src/engine/lib/web
cp web-library/libDeepsEngine.a ../../../../src/engine/lib/web/libDeepsEngine.a
cp web-library/libDeepsEngine.a ../../sys/DeepsEngine/lib/web/libDeepsEngine.a

# serve content
echo "Done building emscripten version of DeepsEngine library in web-library folder"

echo "Cleaning up..."

rm -rf web-library