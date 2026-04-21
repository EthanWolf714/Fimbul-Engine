#!/bin/bash
# Build script for engine
set echo on

mkdir -p ../bin

# Get a list of all the .c files.
cppFilenames=$(find . -type f -name "*.cpp")

# echo "Files:" $cppFilenames

assembly="engine"
compilerFlags="-g -shared -fdeclspec -fPIC"
# -fms-extensions 
# -Wall -Werror
includeFlags="-Isrc -I$VULKAN_SDK/include"
linkerFlags="-lvulkan -lxcb -lX11 -lX11-xcb -lxkbcommon -L$VULKAN_SDK/lib -L/usr/X11R6/lib"
defines="-D_DEBUG -DFEXPORT"

echo "Building $assembly..."
clang++ $cppFilenames $compilerFlags -o ../bin/lib$assembly.so $defines $includeFlags $linkerFlags