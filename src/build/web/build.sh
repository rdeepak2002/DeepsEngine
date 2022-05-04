#!/bin/sh

# allow modification of this folder
sudo chmod -R 777 ./

# download emscripten
./download-emscripten.sh
source emsdk/emsdk_env.sh

# downlaod lua web
./download-lua-web.sh

echo "Creating web build..."

# identify standalone version of app is being built
export STANDALONE="True"

# remove current source code
rm -rf src

# create new folder for source code
mkdir -p src

cp app.html src/app.html
cd src

# build source code
#emcmake cmake ../../../.. "-DVCPKG_CHAINLOAD_TOOLCHAIN_FILE=/Users/deepakramalingam/Documents/Projects/emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake" "-DVCPKG_TARGET_TRIPLET=wasm32-emscripten" "-DCMAKE_TOOLCHAIN_FILE=/Users/deepakramalingam/vcpkg/scripts/buildsystems/vcpkg.cmake" "-DCMAKE_BUILD_TYPE=Release"
emcmake cmake ../../../..
emcc -s USE_GLFW=3 $(mktemp)
emcc -s USE_WEBGL2=1 $(mktemp)
emcc -s USE_ZLIB=1 $(mktemp)
make

# serve content
echo "Serving content..."
http-server -o "/app"