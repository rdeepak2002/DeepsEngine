#!/bin/sh

# clone latest source code
git clone https://github.com/rdeepak2002/DeepsEngine.git
cd DeepsEngine
rm -rf .git

# remove old build directory and replace it with new one
rm -rf build
mv res/example-project/build ../build

# remove source code
rm -rf DeepsEngine

# return to original directory
cd ..
