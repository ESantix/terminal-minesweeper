#!/bin/bash

# Fast compiler with versioned name
BRANCH="$(git rev-parse --abbrev-ref HEAD)"	
VERSION="1.0"
BASE_NAME="run"
FILENAME="$BASE_NAME"_"$BRANCH"_v."$VERSION"
gcc ./src/core.c  -o ./binaries/$FILENAME
#gcc ./src/front-end.cpp -o ./binaries/app-window -lstdc++

# Also run the file for testing
if [ "$1" = "--run" ]; then
    ./binaries/$FILENAME
fi
