#!/bin/sh

cd ..

rm -rf osx
mkdir osx

cd osx

cmake -DCMAKE_BUILD_TYPE=Release ..
make