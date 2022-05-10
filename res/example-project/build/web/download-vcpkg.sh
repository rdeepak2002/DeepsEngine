#!/bin/sh

if [ -d "vcpkg" ]; then
  echo "vcpkg already downloaded..."
else
  echo "Installing vcpkg..."
  git clone https://github.com/Microsoft/vcpkg.git
  rm -rf vcpkg/.git
  ./vcpkg/bootstrap-vcpkg.sh
  export VCPKG_ROOT="$(pwd)/vcpkg"
fi