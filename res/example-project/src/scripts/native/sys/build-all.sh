{ # try
    ./build-mac.sh && echo "Built for macOS"
} || { # catch
  echo "Error buildling for macOS"
}

{ # try
    ./build-web.sh && echo "Built for web"
} || { # catch
  echo "Error buildling for web"
}