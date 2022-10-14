#!/usr/bin/env bash

# project directory
PROJECT_DIR=$(pwd)

# target directory
TARGET_DIR=target

# prepare directory for debug build
BUILD_DIR=$PROJECT_DIR/$TARGET_DIR/debug

# build application
cmake --build "$BUILD_DIR"
