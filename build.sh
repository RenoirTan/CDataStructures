#!/usr/bin/bash

if ! command -v cmake &> /dev/null; then
    echo "Could not find CMake."
    exit 1
else
    echo "CMake found."
fi

cmake --build build/
