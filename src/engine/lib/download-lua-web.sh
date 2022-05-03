# get current lua version from system and the download url for it
LUA_VERSION_TEMP=$(lua -v  | awk  '{print $2}')
LUA_DOWNLOAD_FOLDER_NAME="lua-${LUA_VERSION_TEMP}"
LUA_DOWNLOAD_URL_TEMP="https://www.lua.org/ftp/${LUA_DOWNLOAD_FOLDER_NAME}.tar.gz"

# un zip the lua library to lua-web
rm -rf lua-web
echo "Downloading lua from ${LUA_DOWNLOAD_URL_TEMP}"
curl -L $LUA_DOWNLOAD_URL_TEMP | tar -xz
mv $LUA_DOWNLOAD_FOLDER_NAME lua-web

# make the library for emscripten
cd lua-web
cd src
make generic CC='emcc -s WASM=1' AR='emar rcu' RANLIB='emranlib'
