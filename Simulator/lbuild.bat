@echo off
rm -rf build
mkdir build
cd build
cmake -G Ninja ..
cmake --build .
cp compile_commands.json ../compile_commands.json
cd ..
