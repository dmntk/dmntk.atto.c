#!/usr/bin/env bash

# project directory
PROJECT_DIR=$(pwd)

# prepare directory for debug build
BUILD_DIR=$PROJECT_DIR/target/debug

# build application
ctest --test-dir "$BUILD_DIR"
