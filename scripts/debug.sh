#!/usr/bin/env bash

# project directory
PROJECT_DIR=$(pwd)

# prepare directory for debug build
BUILD_DIR=$PROJECT_DIR/target/debug

# build application
cmake --build "$BUILD_DIR"
