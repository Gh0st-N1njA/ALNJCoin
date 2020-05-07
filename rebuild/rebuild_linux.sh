#!/bin/bash
NUM_PROCS=`cat /proc/cpuinfo | grep proc | wc -l`

cd ..
make clean;
./autogen.sh;
./configure;

make -j${NUM_PROCS}
make install
