#!/bin/sh

cd ..

rm -rf web
mkdir web

find src -name '*.cpp' > ~/lolz2.tmp
FILES_GLOB=$(tr '\n' ' ' < ~/lolz2.tmp)

emcc -std=c++1z -I../../../sys/DeepsEngine/external/lua-5.4.4 -I../../../sys/DeepsEngine/include -Isrc/include ${FILES_GLOB} -s WASM=1 -s SIDE_MODULE=1 -o web/libnative.wasm -DSTANDALONE=TRUE

rm -rf ~/lolz2.tmp