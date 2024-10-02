@echo off
cd build
cmake --build .
cd Debug
Hexapod.exe
cd ../..
