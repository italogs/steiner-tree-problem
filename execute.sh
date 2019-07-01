#!/usr/bin/env bash
export PATH=/usr/bin:$PATH

cd Program
ls
rm steiner
make clean
make
cd ..

mytimestamp=`date "+%d-%m-%y-%H-%M-%S"`
INSTANCES=('b01.stp' 'b02.stp' 'b03.stp' 'b04.stp' 'b05.stp' 'b06.stp' 'b07.stp' 'b08.stp' 'b09.stp' 'b10.stp')

mkdir -p Benchmarks/B/$mytimestamp/ 
for instance in "${INSTANCES[@]}" 
do 
    for seed in {1..5}
    do
        Program/steiner Instances/B/$instance -seed $seed > Benchmarks/B/$mytimestamp/$instance-$seed.txt        
        cat Benchmarks/B/$mytimestamp/$instance-$seed.txt | grep "Final" >> Benchmarks/B/$mytimestamp/compiled-$instance.txt
    done
done


INSTANCES=('b11.stp' 'b12.stp' 'b13.stp' 'b14.stp' 'b15.stp' 'b16.stp' 'b17.stp' 'b18.stp')
for instance in "${INSTANCES[@]}" 
do 
    for seed in {1..5}
    do
        Program/steiner Instances/B/$instance -seed $seed > Benchmarks/B/$mytimestamp/$instance-$seed.txt        
        cat Benchmarks/B/$mytimestamp/$instance-$seed.txt | grep "Final" >> Benchmarks/B/$mytimestamp/compiled-$instance.txt
    done
done
