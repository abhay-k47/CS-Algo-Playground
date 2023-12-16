#!/bin/bash

# This script is a wrapper for CMake. It is used to build the project.

# If the user passes the "clean" argument, the script will delete the build directory.
if [[ -n $1 && $1 = "clean" ]]
then
    echo -n "Cleaning..."
    rm -rf build
    echo "done"
    exit 0
fi

# If the build directory does not exist, it will be created.
if [ ! -d build ]
then
    echo -n "Creating build directory..."
    mkdir build
    echo "done"
fi

# The script will enter the build directory.
echo -n "Entering build directory..."
cd build
echo "done"

# The script will generate the build files.
echo "Generating build files..."
if [[ -n $1 ]]
then
    if [[ $1 == "--trace" ]]
    then
        cmake -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON  .. --trace
    else
        echo "Invalid option: $1"
        echo "Usage: ./build.sh [--trace]"
        exit 1
    fi
else
    cmake ..
fi

# The script will build the project.
echo "Building..."

cmake --build . || exit 1

./test/normalizer_test
# ./app/main
