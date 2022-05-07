#!/bin/sh

# allow modification of this folder
sudo chmod -R 777 ./

if [[ "$OSTYPE" == "linux-gnu"* ]]; then
  echo "OS not yet supported"
elif [[ "$OSTYPE" == "darwin"* ]]; then
  ./setup-macos.sh
elif [[ "$OSTYPE" == "cygwin" ]]; then
  echo "OS not yet supported"
elif [[ "$OSTYPE" == "msys" ]]; then
  echo "OS not yet supported"
elif [[ "$OSTYPE" == "win32" ]]; then
  echo "OS not yet supported"
elif [[ "$OSTYPE" == "freebsd"* ]]; then
  echo "OS not yet supported"
else
  echo "OS not supported"
fi