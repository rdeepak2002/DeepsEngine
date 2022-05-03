echo "Installing command line tools"
sudo xcode-select --install

echo "Installing node and http-server"
brew update
brew install node
sudo chown -R $USER /usr/local/lib/
sudo chown -R $USER /usr/local/lib/node_modules/
sudo chown -R $USER /usr/local/bin/
sudo chown -R $USER /usr/local/share/
brew install http-server

sudo echo "Installing Homebrew"
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

echo "Installing dependencies view Homebrew"
brew install llvm
brew install cmake
brew install glfw3
brew install glew
brew install glm
brew install qt@5
brew install lua@5.3