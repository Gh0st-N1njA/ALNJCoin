#!/bin/bash

NUM_PROCS=`cat /proc/cpuinfo | grep proc | wc -l`

sudo apt-get install -y build-essential libtool bsdmainutils autotools-dev autoconf pkg-config automake python3
sudo apt-get install -y libssl-dev libgmp-dev libevent-dev libboost-all-dev
sudo apt-get install software-properties-common
sudo add-apt-repository ppa:pivx/pivx
sudo apt-get update
sudo apt-get install -y libdb4.8-dev libdb4.8++-dev
sudo apt-get install -y libqt5gui5 libqt5core5a libqt5dbus5 libqt5svg5-dev libqt5charts5-dev qttools5-dev qttools5-dev-tools libprotobuf-dev protobuf-compiler libqrencode-dev


./autogen.sh;
./configure --with-incompatible-bdb;

make -j$NUM_PROCS
make install
