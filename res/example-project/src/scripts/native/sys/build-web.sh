#!/bin/sh

cd ..

rm -rf web
mkdir web

emcc -Isrc/include -Isys/include src/SpinningEntity.cpp -s WASM=1 -s SIDE_MODULE=1 -o web/libnative.wasm