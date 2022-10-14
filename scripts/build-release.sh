#!/usr/bin/env bash

# project directory
PROJECT_DIR=$(pwd)

# target directory
TARGET_DIR=target

# prepare directory for release build
BUILD_DIR=$PROJECT_DIR/$TARGET_DIR/release

# build application
cmake --build "$BUILD_DIR"
