export STANDALONE="True"

# remove current source code
rm -rf src

# create new folder for source code
mkdir -p src
cd src

# build source code
emcmake cmake ../..
emcc -s USE_SDL=2 $(mktemp)
emcc -s USE_ZLIB=1 $(mktemp)
make

# go back to root
cd ..

# serve content
http-server -o "/app"