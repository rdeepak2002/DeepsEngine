#!/bin/sh

cd ..

rm -rf web
mkdir web

emcc SpinningEntity.cpp -s WASM=1 -s SIDE_MODULE=1 -o web/libnative.wasm