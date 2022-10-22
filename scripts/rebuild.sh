#!/usr/bin/env bash

# project directory
PROJECT_DIR=$(pwd)

# build directories
BUILD_DIR_CMAKE_DEBUG=$PROJECT_DIR/cmake-build-debug
BUILD_DIR_CMAKE_RELEASE=$PROJECT_DIR/cmake-build-release

BUILD_DIR_TARGET_DEBUG=$PROJECT_DIR/target/debug
BUILD_DIR_TARGET_RELEASE=$PROJECT_DIR/target/release

# clean build directories
rm -rf "$BUILD_DIR_CMAKE_DEBUG"
rm -rf "$BUILD_DIR_CMAKE_RELEASE"
rm -rf "$BUILD_DIR_TARGET_DEBUG"
rm -rf "$BUILD_DIR_TARGET_RELEASE"

# create empty build directories
mkdir -p "$BUILD_DIR_CMAKE_DEBUG"
mkdir -p "$BUILD_DIR_CMAKE_RELEASE"
mkdir -p "$BUILD_DIR_TARGET_DEBUG"
mkdir -p "$BUILD_DIR_TARGET_RELEASE"

# create build systems
cmake -G Ninja -DCMAKE_BUILD_TYPE=Debug   -DCMAKE_MAKE_PROGRAM=ninja -S "$PROJECT_DIR" -B "$BUILD_DIR_CMAKE_DEBUG"
cmake -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_MAKE_PROGRAM=ninja -S "$PROJECT_DIR" -B "$BUILD_DIR_CMAKE_RELEASE"
cmake -G Ninja -DCMAKE_BUILD_TYPE=Debug   -DCMAKE_MAKE_PROGRAM=ninja -S "$PROJECT_DIR" -B "$BUILD_DIR_TARGET_DEBUG"
cmake -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_MAKE_PROGRAM=ninja -S "$PROJECT_DIR" -B "$BUILD_DIR_TARGET_RELEASE"

