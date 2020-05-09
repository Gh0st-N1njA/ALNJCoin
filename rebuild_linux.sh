#!/bin/bash
alnj-cli stop
alnj-cli -testnet stop
alnj-cli -regtest stop
git pull
NUM_PROCS=`cat /proc/cpuinfo | grep proc | wc -l`
let "NUM_PROCS--";

make -j${NUM_PROCS}
sudo make install

rm -rf ~/.alnj
alnjd -daemon -testnet -debug
