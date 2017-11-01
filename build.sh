#! /bin/bash

cd build/
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -DPC_BUILD=1
cmake --build .
echo "build completed"
