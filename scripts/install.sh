echo "Installing command line tools"
sudo xcode-select --install

echo "Installing git"
brew install git

echo "Installing node and http-server"
brew update
brew install http-server

sudo echo "Installing Homebrew"
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

echo "Installing dependencies via Homebrew"
brew install llvm
brew install cmake
brew install glfw3
brew install glew
brew install qt@5

echo "Installing dependencies via vcpkg"
vcpkg install lua