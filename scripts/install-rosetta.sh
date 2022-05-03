sudo echo "Installing Homebrew"
arch -x86_64 zsh
arch -x86_64 /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install.sh)"

echo "Installing dependencies view Homebrew"
arch -x86_64 /usr/local/bin/brew install llvm
arch -x86_64 /usr/local/bin/brew install cmake
arch -x86_64 /usr/local/bin/brew install glfw3
arch -x86_64 /usr/local/bin/brew install glew
arch -x86_64 /usr/local/bin/brew install glm
arch -x86_64 /usr/local/bin/brew install qt@5
arch -x86_64 /usr/local/bin/brew install lua@5.3