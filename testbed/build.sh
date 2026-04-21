#!/bin/bash
# Build script for testbed
set echo on

mkdir -p ../bin

# Get a list of all the .cpp files.
cppFilenames=$(find . -type f -name "*.cpp")

# echo "Files:" $cppFilenames

assembly="testbed"
compilerFlags="-g -fdeclspec -fPIC" 
# -fms-extensions 
# -Wall -Werror
includeFlags="-Isrc -I../engine/src/"
# links to engine library
linkerFlags="-L../bin/ -lengine -Wl,-rpath,." #path to linked binarys 
defines="-D_DEBUG -DFIMPORT"

echo "Building $assembly..."
echo clang $cppFilenames $compilerFlags -o ../bin/$assembly $defines $includeFlags $linkerFlags
clang++ $cppFilenames $compilerFlags -o ../bin/$assembly $defines $includeFlags $linkerFlags