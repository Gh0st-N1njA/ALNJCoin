#!/bin/bash
pactumcoin-cli stop
pactumcoin-cli -testnet stop
pactumcoin-cli -regtest stop
git pull
NUM_PROCS=`cat /proc/cpuinfo | grep proc | wc -l`
let "NUM_PROCS--";

make -j${NUM_PROCS}
sudo make install

rm -rf ~/.pctm
pactumcoind -daemon -testnet -debug
