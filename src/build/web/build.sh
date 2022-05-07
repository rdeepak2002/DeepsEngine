#!/bin/sh

# allow modification of this folder
sudo chmod -R 777 ./

echo ${DEEPS_ENGINE_RESOURCE_DIRECTORY}

if [[ -v DEEPS_ENGINE_RESOURCE_DIRECTORY ]];
then
    echo "Resource directory set to ${DEEPS_ENGINE_RESOURCE_DIRECTORY}"
else
    echo "Error: DEEPS_ENGINE_RESOURCE_DIRECTORY env variable not provided!"
    exit 1
fi

# download emscripten
./download-emscripten.sh
source emsdk/emsdk_env.sh

# install vcpkg stuff
./download-vcpkg.sh
export VCPKG_ROOT="$(pwd)/vcpkg"
./vcpkg/vcpkg install lua:wasm32-emscripten

echo "Creating web build..."

# remove current source code
rm -rf build

# create new folder for source code
mkdir -p build/assets
cp app.html build/app.html
cp -R ${DEEPS_ENGINE_RESOURCE_DIRECTORY} build/assets/res

# build source code
cmake -S ./ -B build "-DVCPKG_CHAINLOAD_TOOLCHAIN_FILE=$(pwd)/emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake" "-DCMAKE_TOOLCHAIN_FILE=$(pwd)/vcpkg/scripts/buildsystems/vcpkg.cmake" "-DVCPKG_TARGET_TRIPLET=wasm32-emscripten"
cmake --build build

# serve content
echo "Serving content from /build/app.html"
http-server -o "/build/app.html" --silent