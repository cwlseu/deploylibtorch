#!/bin/bash

if [ ! -d build ]; then 
mkdir build 
fi
cd build 
cmake .. && make -j4
./test_run_tracemodel_indir ../models
cd -
