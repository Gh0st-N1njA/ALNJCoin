#!/bin/bash
NUM_PROCS=`cat /proc/cpuinfo | grep proc | wc -l`

make clean;
./autogen.sh;
./configure;

make -j${NUM_PROCS}
make install
