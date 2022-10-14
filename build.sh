#!/usr/bin/env bash

# treat the current working directory as the root
# project directory where all sources are stored
PROJECT_DIR=$(pwd)

# prepare directory for debug build
DEBUG_BUILD_DIR=$PROJECT_DIR/cmake-build-debug

# clean debug build directory
rm -rf "$DEBUG_BUILD_DIR"

# create empty debug build directory
mkdir "$DEBUG_BUILD_DIR"

# prepare build system for the project
cmake -G Ninja -DCMAKE_BUILD_TYPE=Debug -DCMAKE_MAKE_PROGRAM=ninja -S "$PROJECT_DIR" -B "$DEBUG_BUILD_DIR"



