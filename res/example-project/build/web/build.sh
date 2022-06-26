#!/bin/sh

# allow modification of this folder
sudo chmod -R 777 ./

echo ${DEEPS_ENGINE_RESOURCE_DIRECTORY}

if [[ -z "${DEEPS_ENGINE_RESOURCE_DIRECTORY}" ]]; then
  # quick solution: export DEEPS_ENGINE_RESOURCE_DIRECTORY=/Users/deepakramalingam/Desktop/example-project/src
  echo "Error: DEEPS_ENGINE_RESOURCE_DIRECTORY env variable not provided! This is the directory of the project src folder."
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

echo "Creating web build..."

# remove current source code
#rm -rf build
rm -rf build/assets

# create new folder for source code
mkdir -p build/assets/project/src
mkdir -p assets/project/src
cp app.html build/app.html
cp firebase.json build/firebase.json
# allow access to dylib for native scripting
cp -R ${DEEPS_ENGINE_RESOURCE_DIRECTORY} build/assets/project
# fix preloading issues
cp -R ${DEEPS_ENGINE_RESOURCE_DIRECTORY} assets/project

# remove unused native script libraries
rm -rf assets/project/src/scripts/native/cmake-build-debug
rm -rf assets/project/src/scripts/native/.idea
rm -rf assets/project/src/scripts/native/src
rm -rf assets/project/src/scripts/native/sys

# build source code
rm -rf build/DeepsEngine.data

if [ -f "build/DeepsEngine.js" ]; then
  echo "Generating quick build"
  mkdir build/tmp
  emcc --use-preload-plugins -IDeepsEngine/include -Ilua-5.4.4/src -Iyaml-cpp/include -Lyaml-cpp/src -Lassimp-5.0.1/build/code -std=c++1z -sASSERTIONS -s LLD_REPORT_UNDEFINED -s ALLOW_MEMORY_GROWTH=1 -s USE_WEBGL2=1 -s MIN_WEBGL_VERSION=2 -s MAX_WEBGL_VERSION=2 -s FULL_ES3=1 -s USE_GLFW=3 -s MAIN_MODULE=1 -s ASYNCIFY -s "ASYNCIFY_IMPORTS=['doLoadLibrary']" -s FORCE_FILESYSTEM=1 -s "EXTRA_EXPORTED_RUNTIME_METHODS=['FS','ccall','cwrap']" DeepsEngine/lib/web/libDeepsEngine.a yaml-cpp/src/libyaml-cpp.a lua-5.4.4/src/liblua.a assimp-5.0.1/lib/libassimp.a assimp-5.0.1/lib/libIrrXML.a assimp-5.0.1/lib/libzlib.a main.cpp -fPIC -o build/tmp/DeepsEngine.html --preload-file assets -DSTANDALONE=TRUE -DCMAKE_POSITION_INDEPENDENT_CODE=ON
  mv build/tmp/DeepsEngine.data build/DeepsEngine.data
  rm -rf build/tmp
else
  echo "Generating build for both engine and project (this will take a long time)"

  rm -rf build/DeepsEngine.html
  rm -rf build/DeepsEngine.js
  rm -rf build/DeepsEngine.wasm

  emcc --use-preload-plugins -IDeepsEngine/include -Ilua-5.4.4/src -Iyaml-cpp/include -Lyaml-cpp/src -Lassimp-5.0.1/build/code -std=c++1z -sASSERTIONS -s LLD_REPORT_UNDEFINED -s ALLOW_MEMORY_GROWTH=1 -s USE_WEBGL2=1 -s MIN_WEBGL_VERSION=2 -s MAX_WEBGL_VERSION=2 -s FULL_ES3=1 -s USE_GLFW=3 -s MAIN_MODULE=1 -s ASYNCIFY -s "ASYNCIFY_IMPORTS=['doLoadLibrary']" -s FORCE_FILESYSTEM=1 -s "EXTRA_EXPORTED_RUNTIME_METHODS=['FS','ccall','cwrap']" DeepsEngine/lib/web/libDeepsEngine.a yaml-cpp/src/libyaml-cpp.a lua-5.4.4/src/liblua.a assimp-5.0.1/lib/libassimp.a assimp-5.0.1/lib/libIrrXML.a assimp-5.0.1/lib/libzlib.a main.cpp -fPIC -o build/DeepsEngine.html --preload-file assets -DSTANDALONE=TRUE -DCMAKE_POSITION_INDEPENDENT_CODE=ON -Os
fi

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