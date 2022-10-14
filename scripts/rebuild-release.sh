#!/usr/bin/env bash

# project directory
PROJECT_DIR=$(pwd)

# target directory
TARGET_DIR=target

# debug build directory
BUILD_DIR=$PROJECT_DIR/$TARGET_DIR/release

# clean debug build directory
rm -rf "$BUILD_DIR"

# create empty debug build directory
mkdir -p "$BUILD_DIR"

# prepare build system for release target
cmake -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_MAKE_PROGRAM=ninja -S "$PROJECT_DIR" -B "$BUILD_DIR"
