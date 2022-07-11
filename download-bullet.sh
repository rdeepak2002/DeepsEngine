#!/bin/sh

tar -xvf bullet3-3.24.tar.gz

cd bullet3-3.24
./build_cmake_pybullet_double.sh
cd ..