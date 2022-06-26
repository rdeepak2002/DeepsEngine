#!/bin/sh

cd ..

rm -rf web
mkdir web

emcc -std=c++1z -Isys/lua-5.4.4/src -Isrc/include -Isys/include src/SpinningEntity.cpp -s WASM=1 -s SIDE_MODULE=1 -o web/libnative.wasm -DSTANDALONE=TRUE