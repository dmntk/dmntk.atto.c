#!/usr/bin/env bash

# project directory
PROJECT_DIR=$(pwd)

# prepare directory for release build
BUILD_DIR=$PROJECT_DIR/target/release

# build application
cmake --build "$BUILD_DIR"
