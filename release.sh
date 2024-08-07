#!/bin/bash

BUILD_DIR="build-release"

rm -rf "$BUILD_DIR"
rm -rf bin

cmake -B "$BUILD_DIR" -DCMAKE_BUILD_TYPE=Release && cmake --build "$BUILD_DIR" -j