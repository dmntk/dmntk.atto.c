#!/usr/bin/env bash

# project directory
PROJECT_DIR=$(pwd)

# clean CLion output directories
rm -rf "$PROJECT_DIR/target"
rm -rf "$PROJECT_DIR/cmake-build-debug"
rm -rf "$PROJECT_DIR/cmake-build-release"
