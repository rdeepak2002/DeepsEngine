#!/bin/sh

# allow modification of this folder
sudo chmod -R 777 ./

echo ${DEEPS_ENGINE_RESOURCE_DIRECTORY}

if [[ -z "${DEEPS_ENGINE_RESOURCE_DIRECTORY}" ]]; then
  # quick solution: export DEEPS_ENGINE_RESOURCE_DIRECTORY=/Users/deepakramalingam/Desktop/example-project/src
  echo "Error: DEEPS_ENGINE_RESOURCE_DIRECTORY env variable not provided! This is the directory of the project src folder."
  echo "Quick solution: export DEEPS_ENGINE_RESOURCE_DIRECTORY=/Users/deepakramalingam/Desktop/example-project/src"
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

source emsdk/emsdk_env.sh

echo "Creating web build..."

# remove current source code
rm -rf build

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
echo "Generating build for both engine and project (this will take a long time)"

emcc -g --use-preload-plugins -lopenal -I../../sys/DeepsEngine/include -I../../sys/DeepsEngine/external/lua-5.4.4 -I../../sys/DeepsEngine/external/bullet-2.82/src -std=c++1z -sASSERTIONS -s LLD_REPORT_UNDEFINED -s ALLOW_MEMORY_GROWTH=1 -s USE_WEBGL2=1 -s MIN_WEBGL_VERSION=2 -s MAX_WEBGL_VERSION=2 -s FULL_ES3=1 -s USE_GLFW=3 -s USE_BULLET=1 -s USE_VORBIS=1 -s USE_OGG=1 -s USE_SDL_MIXER=2 -s USE_SDL_NET=2 -s MAIN_MODULE=1 -s FORCE_FILESYSTEM=1 -s "EXTRA_EXPORTED_RUNTIME_METHODS=['FS','ccall','cwrap']" ../../sys/DeepsEngine/lib/web/libDeepsEngine.a yaml-cpp/src/libyaml-cpp.a lua-5.4.4/src/liblua.a assimp-5.0.1/lib/libassimp.a assimp-5.0.1/lib/libIrrXML.a assimp-5.0.1/lib/libzlib.a main.cpp -fPIC -o build/DeepsEngine.html --preload-file assets -DSTANDALONE=TRUE -DCMAKE_POSITION_INDEPENDENT_CODE=ON -O0

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

say 'Web build complete.'

exit 0