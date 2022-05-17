#!/bin/sh

tar -xvf assimp-5.0.1.tar.gz

source emsdk/emsdk_env.sh

cd assimp-5.0.1
emcmake cmake -DCMAKE_BUILD_TYPE=Release .
emmake make
cd ..