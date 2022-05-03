echo "Installing command line tools"
sudo xcode-select --install

echo "Installing git"
brew install git

echo "Installing node and http-server"
brew update
brew install node
sudo chown -R $USER /usr/local/lib/
sudo chown -R $USER /usr/local/lib/node_modules/
sudo chown -R $USER /usr/local/bin/
sudo chown -R $USER /usr/local/share/
brew install http-server

echo "Installing Homebrew"
arch -x86_64 zsh
arch -x86_64 /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install.sh)"

echo "Installing dependencies via Homebrew"
arch -x86_64 /usr/local/bin/brew install llvm
arch -x86_64 /usr/local/bin/brew install cmake
arch -x86_64 /usr/local/bin/brew install glfw3
arch -x86_64 /usr/local/bin/brew install glew
arch -x86_64 /usr/local/bin/brew install qt@5
arch -x86_64 /usr/local/bin/brew install lua@5.3