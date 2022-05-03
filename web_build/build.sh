## script to build web application
#
## Get the emsdk repo
#git clone https://github.com/emscripten-core/emsdk.git
#
## Enter that directory
#cd emsdk
#
## Fetch the latest version of the emsdk (not needed the first time you clone)
#git pull
#
## Download and install the latest SDK tools.
#./emsdk install latest
#
## Make the "latest" SDK "active" for the current user. (writes .emscripten file)
#./emsdk activate latest
#
## Activate PATH and other environment variables in the current terminal
#source ./emsdk_env.sh
#
#cd ..

# identify standalone version of app is being built
export STANDALONE="True"

# remove current source code
rm -rf src

# create new folder for source code
mkdir -p src

sudo chmod -R 777 ./

# becareful cuz shaders work differently on web
rm -rf assets/res
cp -R ../res assets/res
cp -R assets src/assets
cp app.html src/app.html

cd src

# build source code
#emcmake cmake ../.. "-DVCPKG_CHAINLOAD_TOOLCHAIN_FILE=/Users/deepakramalingam/Documents/Projects/emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake" "-DVCPKG_TARGET_TRIPLET=wasm32-emscripten" "-DCMAKE_TOOLCHAIN_FILE=/Users/deepakramalingam/vcpkg/scripts/buildsystems/vcpkg.cmake" "-DCMAKE_BUILD_TYPE=Release"
emcmake cmake ../..
emcc -s USE_GLFW=3 $(mktemp)
emcc -s USE_WEBGL2=1 $(mktemp)
emcc -s USE_ZLIB=1 $(mktemp)
make

# go back to root
#cd ..

# serve content
http-server -o "/app"