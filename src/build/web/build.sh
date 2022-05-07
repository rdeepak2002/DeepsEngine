#!/bin/sh

# allow modification of this folder
sudo chmod -R 777 ./

# download emscripten
./download-emscripten.sh
source emsdk/emsdk_env.sh

# install vcpkg stuff
./download-vcpkg.sh
export VCPKG_ROOT="$(pwd)/vcpkg"
./vcpkg/vcpkg install lua:wasm32-emscripten

echo "Creating web build..."

# remove current source code
rm -rf src

# create new folder for source code
mkdir -p build/assets
cp app.html build/app.html
cp -R /Users/deepakramalingam/Documents/Projects/DeepsEngine/res build/assets/res

# build source code
cmake -S ./ -B build "-DVCPKG_CHAINLOAD_TOOLCHAIN_FILE=$(pwd)/emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake" "-DCMAKE_TOOLCHAIN_FILE=$(pwd)/vcpkg/scripts/buildsystems/vcpkg.cmake" "-DVCPKG_TARGET_TRIPLET=wasm32-emscripten"
cmake --build build

# serve content
echo "Serving content..."
http-server -o "/build/app" --silent