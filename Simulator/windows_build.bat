@echo off
rm -rf build
mkdir build
cd build
cmake ..
cmake --build .
cd Debug
Hexapod.exe
cd ..
cd ..
