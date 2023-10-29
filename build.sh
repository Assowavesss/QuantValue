#!/bin/bash

# Set the path to your CMakeLists.txt file
CMAKE_PROJECT_DIR="."

# Set the build directory
BUILD_DIR="build"

# Set the path to install directory
INSTALL_DIR="installed"

# Remove build and install directories
rm -rf "$BUILD_DIR"
rm -rf "$INSTALL_DIR"

# Configure the project
cmake -S "$CMAKE_PROJECT_DIR" -B "$BUILD_DIR" "$@"

# Build the project
cmake --build "$BUILD_DIR" --config Release

# Install the project
cmake --install "$BUILD_DIR" --prefix "$INSTALL_DIR"
