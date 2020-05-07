#!/bin/bash

sudo apt-get install -y build-essential libtool bsdmainutils autotools-dev autoconf pkg-config automake python3
sudo apt-get install -y libssl-dev libgmp-dev libevent-dev libboost-all-dev
sudo apt-get install -y software-properties-common
sudo add-apt-repository -y ppa:pivx/pivx
sudo apt-get update
sudo apt-get install -y libdb4.8-dev libdb4.8++-dev
sudo apt-get install -y libqt5gui5 libqt5core5a libqt5dbus5 libqt5svg5-dev libqt5charts5-dev qttools5-dev qttools5-dev-tools libprotobuf-dev protobuf-compiler libqrencode-dev
sudo apt-get install -y libzmq3-dev

