#!/bin/bash

# Fast compiler with versioned name
gcc ./src/main.c  -o ./binaries/minesweeper

# Also run the file for testing
if [ "$1" = "--run" ]; then
    ./binaries/minesweeper
fi



