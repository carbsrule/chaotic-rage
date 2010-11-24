#!/bin/bash

# Where is 'crossenv' installed?
CROSSENV="/home/josh/crossenv"

# You will want an install of crossenv with the following packages:
#  - core
#  - libsdl
#  - libzzip
#  - libconfuse
#  - libsdl-mixer
#  - libsdl-image
#  - opengl


PREFIX="$CROSSENV/environments/i386-mingw32"
PATH="$PREFIX/bin:$PREFIX/local/bin:$PREFIX/$PLATFORM/bin:$PATH"
export PATH

make clean
make CXX="i386-mingw32-g++" all
