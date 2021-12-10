#!/usr/bin/env bash

make lib -j
mkdir -p "$1"/include
mkdir "$1"/lib
cp -r imageio/include "$1"
mv imageio/lib/libimageio.so "$1/lib/libimageio.so"
