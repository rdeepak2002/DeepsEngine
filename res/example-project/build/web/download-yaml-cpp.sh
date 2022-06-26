#!/bin/sh

source emsdk/emsdk_env.sh

rm -rf yaml-cpp
tar -xvf yaml-cpp.tgz
cd yaml-cpp
cd src
emcmake cmake -DCMAKE_BUILD_TYPE=Release ..
emmake make