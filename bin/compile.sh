#!/usr/bin/env bash

make clean

> bin/settings
echo "CXX=g++" >> bin/settings
echo "ARCH=x86_64" >> bin/settings
make imageio -j

> bin/settings
echo "CXX=aarch64-linux-gnu-g++" >> bin/settings
echo "ARCH=aarch64" >> bin/settings
rm -f obj/*.o
make imageio -j
