#!/bin/sh

# get current lua version from system and the download url for it
LUA_VERSION_TEMP=$(lua -v  | awk  '{print $2}')
LUA_DOWNLOAD_FOLDER_NAME="lua-${LUA_VERSION_TEMP}"
LUA_DOWNLOAD_URL_TEMP="https://www.lua.org/ftp/${LUA_DOWNLOAD_FOLDER_NAME}.tar.gz"

# exit early if lua already downloaded
if [ -d "${LUA_DOWNLOAD_FOLDER_NAME}" ]; then
  echo "Lua web already downloaded..."
else
  echo "Re-downloading emscripten..."
#  rm -rf emsdk
  ./download-emscripten.sh

  echo "Downloading ${LUA_DOWNLOAD_FOLDER_NAME} and building lua for web..."

  # un zip the lua library to lua-web
  rm -rf $LUA_DOWNLOAD_FOLDER_NAME
  echo "Downloading lua from ${LUA_DOWNLOAD_URL_TEMP}"
  curl -L $LUA_DOWNLOAD_URL_TEMP | tar -xz

  # make the library for emscripten
  cd $LUA_DOWNLOAD_FOLDER_NAME
  cd src
  make generic CC='emcc -s WASM=1' AR='emar rcu' RANLIB='emranlib'

  cd ..
  cd ..
fi
