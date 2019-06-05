#!/usr/bin/env bash
export PATH=/usr/bin:$PATH

cd Program
ls
rm pc-steiner
make clean
make
cd ..
