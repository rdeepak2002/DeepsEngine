#!/bin/sh

# allow modification of this folder
sudo chmod -R 777 ./

rm -rf emsdk
rm -rf vcpkg
rm -rf web-library

# download emscripten
./download-emscripten.sh
source emsdk/emsdk_env.sh

# install vcpkg stuff
./download-vcpkg.sh
export VCPKG_ROOT="$(pwd)/vcpkg"
./vcpkg/vcpkg install lua:wasm32-emscripten
./vcpkg/vcpkg install yaml-cpp:wasm32-emscripten
#./vcpkg/vcpkg install assimp:wasm32-emscripten

# download assimp for web
if [ -d "assimp-5.0.1" ]; then
  echo "Assimp already built..."
else
  echo "Building Assimp..."
  ./download-assimp.sh
fi

echo "Creating web library..."

# remove current library code
rm -rf web-library

# build source code
export AS_LIBRARY=""
cmake -S ../../../.. -B web-library "-DVCPKG_CHAINLOAD_TOOLCHAIN_FILE=$(pwd)/emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake" "-DCMAKE_TOOLCHAIN_FILE=$(pwd)/vcpkg/scripts/buildsystems/vcpkg.cmake" "-DVCPKG_TARGET_TRIPLET=wasm32-emscripten"
cmake --build web-library

# copy compiled library to engine lib folder
mkdir -p ../../../../src/engine/lib/web
cp web-library/libDeepsEngine.a ../../../../src/engine/lib/web/libDeepsEngine.a
cp web-library/libDeepsEngine.a DeepsEngine/lib/web/libDeepsEngine.a

# serve content
echo "Done building emscripten version of DeepsEngine library in web-library folder"

echo "Cleaning up..."

rm -rf emsdk
rm -rf vcpkg
rm -rf web-library