#!/bin/bash
#
# Does a native build and an emscripten build of the various test scripts
#

set -e
set -v
export EMCC_DEBUG=1

# Clean up previous test results
rm -f tests/*.o tests/*.bc tests/*.js tests/*.js.map tests/*.gcc tests/*.clang

# Basic hello world
g++ tests/hello.cpp -o tests/hello.gcc
clang++ tests/hello.cpp -o tests/hello.clang
em++ tests/hello.cpp -o tests/hello.js

# Bullet physics
g++ tests/bullet.cpp `pkg-config --cflags bullet` -c -o tests/bullet.o
g++ tests/bullet.o `pkg-config --libs bullet` -o tests/bullet.native
emcc tests/bullet.cpp `pkg-config --cflags bullet` -c -o tests/bullet.bc
emcc tests/bullet.bc lib/libBulletDynamics.bc lib/libBulletCollision.bc lib/libLinearMath.bc -o tests/bullet.js