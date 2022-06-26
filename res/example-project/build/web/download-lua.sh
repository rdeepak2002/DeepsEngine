#!/bin/sh

source emsdk/emsdk_env.sh

rm -rf lua-5.4.4
tar -xvf lua-5.4.4.tar.gz
cd lua-5.4.4
cd src
make generic MYCFLAGS=-fPIC CC='emcc -s WASM=1' AR='emar rcu' RANLIB='emranlib'
