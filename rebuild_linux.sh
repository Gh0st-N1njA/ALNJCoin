#!/bin/bash
git pull
NUM_PROCS=`cat /proc/cpuinfo | grep proc | wc -l`
let "NUM_PROCS--";

make -j${NUM_PROCS}
sudo make install
alnj-cli stop
alnj-cli -testnet stop
rm -rf ~/.alnj
alnjd -daemon -testnet -debug
