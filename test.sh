#!/bin/bash

if [ ! -d build ]; then 
mkdir build 
fi
cd build 
cmake .. && make -j4
./example-app ../models/mobilenetv2-128_S-cpu.pt
cd -
