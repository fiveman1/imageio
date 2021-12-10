#!/usr/bin/env bash

make lib -j
mkdir -p "$1"/include
mkdir "$1"/lib
cp -r include "$1"
mv lib/libimageio.so "$1/lib/libimageio.so"
