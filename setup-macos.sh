#!/bin/sh

# allow modification of this folder
sudo chmod -R 777 ./

# install command line tools for c compilation
echo "Installing command line tools"
sudo xcode-select --install

# download homebrew (if not already installed)
which -s brew
if [[ $? != 0 ]] ; then
  sudo echo "Installing Homebrew"
  /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
else
  sudo echo "Updating Homebrew"
  brew update
fi

# git is a necessity for pulling packages
echo "Installing git"
brew install git

# http-server to serve content of web build
echo "Installing node and http-server"
brew update
brew install http-server

# necessary downloads for c++ compilation
echo "Installing dependencies via Homebrew"
brew install llvm
brew install cmake

# additional downloads for vcpkg
brew install autoconf
brew install autoconf-archive
brew install automake
brew install bison
brew install gettext
brew install gfortran
brew install gperf
brew install gtk-doc
brew install libtool
brew install meson
brew install mono
brew install nasm
brew install pkg-config
brew install texinfo
brew install yasm

# download vcpkg (if not already installed) for installing libraries in a cross platform manner
if [ -d "vcpkg" ]; then
  echo "vcpkg already downloaded..."
else
  echo "Installing vcpkg..."
  git clone https://github.com/Microsoft/vcpkg.git
  rm -rf vcpkg/.git
  ./vcpkg/bootstrap-vcpkg.sh
  export VCPKG_ROOT="$(pwd)/vcpkg"
fi

# install c++ libraries via vcpkg
echo "Installing dependencies via vcpkg"
./vcpkg/vcpkg install lua
./vcpkg/vcpkg install glfw3
./vcpkg/vcpkg install qt5