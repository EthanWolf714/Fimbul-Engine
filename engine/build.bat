
REM Build script for engine
@ECHO OFF
SetLocal EnableDelayedExpansion

REM Get a list of all the .c files.
SET cppFilenames=
FOR /R %%f in (*.cpp) do (
    SET cppFilenames=!cppFilenames! %%f
)

REM echo "Files:" %cppFilenames%

SET assembly=engine
SET compilerFlags=-g -shared -fuse-ld=lld --target=x86_64-w64-mingw32 -Wvarargs -Wall -Werror 
REM -Wall -Werror
SET includeFlags=-Isrc -I%VULKAN_SDK%/Include
SET linkerFlags=-luser32 -lvulkan-1 -L%VULKAN_SDK%/Lib 
SET defines=-D_DEBUG -DFEXPORT -D_CRT_SECURE_NO_WARNINGS -D_ITERATOR_DEBUG_LEVEL=0
SET CC=C:\Program Files\LLVM\bin\clang++.exe
ECHO "Building %assembly%%..."
"%CC%" %cppFilenames% %compilerFlags% -o ../bin/%assembly%.dll %defines% %includeFlags% %linkerFlags%