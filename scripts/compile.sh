#!/bin/bash

# Fast compiler with versioned name
gcc ./src/core.c  -o ./binaries/minesweeper

# Also run the file for testing
if [ "$1" = "--run" ]; then
    ./binaries/minesweeper
fi



