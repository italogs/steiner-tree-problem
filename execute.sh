#!/usr/bin/env bash
export PATH=/usr/bin:$PATH

cd Program
ls
rm steiner
make clean
make
cd ..


./Program/steiner Instances/B/b01.stp -seed 1