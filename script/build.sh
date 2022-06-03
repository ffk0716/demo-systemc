#!/usr/bin/env bash
root=$(dirname $(realpath $0))/..

mkdir build
pushd build
cmake $root
make -j$(nproc)
popd

