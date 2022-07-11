#!/bin/sh

wget -O bullet3-3.24.tar.gz https://github.com/bulletphysics/bullet3/archive/refs/tags/3.24.tar.gz

tar -xvf bullet3-3.24.tar.gz

cd bullet3-3.24
./build_cmake_pybullet_double.sh
cd ..