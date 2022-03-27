export STANDALONE="True"

cd build
emcmake cmake ..
emcc -s USE_SDL=2 $(mktemp)
emcc -s USE_ZLIB=1 $(mktemp)
make

http-server -o "/app"