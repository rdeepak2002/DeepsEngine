#!/bin/sh

# allow modification of this folder
sudo chmod -R 777 ./

# download emscripten
./download-emscripten.sh
source emsdk/emsdk_env.sh

echo "Creating web build..."

# identify standalone version of app is being built
export STANDALONE="True"

# remove current source code
rm -rf src

# create new folder for source code
mkdir -p src
mkdir -p src/build/assets

#cp app.html src/app.html
cp app.html src/build/app.html
cd src

# build source code
cmake -S ../../../.. -B build "-DVCPKG_CHAINLOAD_TOOLCHAIN_FILE=/Users/deepakramalingam/Documents/Projects/DeepsEngine/src/build/web/emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake" "-DCMAKE_TOOLCHAIN_FILE=~/vcpkg/scripts/buildsystems/vcpkg.cmake" "-DVCPKG_TARGET_TRIPLET=wasm32-emscripten"
cmake --build build

# serve content
echo "Serving content..."
http-server -o "/build/app"