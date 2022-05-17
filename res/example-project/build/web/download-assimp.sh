#!/bin/sh

curl https://github.com/assimp/assimp/archive/refs/tags/v5.0.1.zip
unzip assimp-5.0.1.zip
rm -rf assimp-5.0.1.zip

source emsdk/emsdk_env.sh

cd assimp-5.0.1
emcmake cmake -DCMAKE_BUILD_TYPE=Release .
emmake make
cd ..