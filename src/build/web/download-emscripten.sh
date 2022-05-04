#!/bin/sh

if [ -d "emsdk" ]; then
  echo "Emscripten already downloaded..."
else
  # script to build web application
  echo "Downloading and building emscripten..."

  # Delete current directory
  rm -rf emsdk

  # Get the emsdk repo
  git clone https://github.com/emscripten-core/emsdk.git emsdk
fi

# Enter that directory
cd emsdk

# Fetch the latest version of the emsdk (not needed the first time you clone)
git pull

# Download and install the latest SDK tools.
./emsdk install latest

# Make the "latest" SDK "active" for the current user. (writes .emscripten file)
./emsdk activate latest

# Activate PATH and other environment variables in the current terminal
source ./emsdk_env.sh

cd ..