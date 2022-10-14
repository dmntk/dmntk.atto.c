#!/usr/bin/env bash

# project directory
PROJECT_DIR=$(pwd)

# build directories
DEBUG_BUILD_DIR=$PROJECT_DIR/cmake-build-debug
RELEASE_BUILD_DIR=$PROJECT_DIR/cmake-build-release

# clean build directories
rm -rf "$DEBUG_BUILD_DIR"
rm -rf "$RELEASE_BUILD_DIR"

# create empty build directories
mkdir -p "$DEBUG_BUILD_DIR"
mkdir -p "$RELEASE_BUILD_DIR"

# create build system
cmake -G Ninja -DCMAKE_BUILD_TYPE=Debug   -DCMAKE_MAKE_PROGRAM=ninja -S "$PROJECT_DIR" -B "$DEBUG_BUILD_DIR"
cmake -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_MAKE_PROGRAM=ninja -S "$PROJECT_DIR" -B "$RELEASE_BUILD_DIR"

