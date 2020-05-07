#!/bin/bash
git pull
NUM_PROCS=`cat /proc/cpuinfo | grep proc | wc -l`
let "NUM_PROCS--";

make clean;
./autogen.sh;
./configure;

make -j${NUM_PROCS}
make install

