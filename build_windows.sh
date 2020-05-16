#!/bin/bash
git pull
NUM_PROCS=`cat /proc/cpuinfo | grep proc | wc -l`
let "NUM_PROCS--";

make clean
PATH=$(echo "$PATH" | sed -e 's/:\/mnt.*//g') # strip out problematic Windows %PATH% imported var
cd depends
make HOST=x86_64-w64-mingw32 -j${NUM_PROCS}
cd ..
./autogen.sh # not required when building from tarball
CONFIG_SITE=$PWD/depends/x86_64-w64-mingw32/share/config.site ./configure --prefix=/
make -j${NUM_PROCS}
make deploy
