# allow modification of this folder
sudo chmod -R 777 ./

echo "Installing command line tools"
sudo xcode-select --install

which -s brew
if [[ $? != 0 ]] ; then
  sudo echo "Installing Homebrew"
  /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
else
  sudo echo "Updating Homebrew"
  brew update
fi

echo "Installing git"
brew install git

echo "Installing node and http-server"
brew update
brew install http-server

echo "Installing dependencies via Homebrew"
brew install llvm
brew install cmake
brew install glfw3
brew install glew
brew install qt@5

if [ -d "vcpkg" ]; then
  echo "vcpkg already downloaded..."
else
  echo "Installing vcpkg..."
  git clone https://github.com/Microsoft/vcpkg.git
  rm -rf vcpkg/.git
  ./vcpkg/bootstrap-vcpkg.sh
  export VCPKG_ROOT="$(pwd)/vcpkg"
fi

echo "Installing dependencies via vcpkg"
./vcpkg/vcpkg install lua
./vcpkg/vcpkg install glfw3