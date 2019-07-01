#!/usr/bin/env bash
export PATH=/usr/bin:$PATH

cd Program
ls
rm steiner
make clean
make
cd ..

mytimestamp=`date "+%d-%m-%y-%H-%M-%S"`


#Set B
INSTANCES=('b01.stp' 'b02.stp' 'b03.stp' 'b04.stp' 'b05.stp' 'b06.stp' 'b07.stp' 'b08.stp' 'b09.stp' 'b10.stp' 'b11.stp' 'b12.stp' 'b13.stp' 'b14.stp' 'b15.stp' 'b16.stp' 'b17.stp' 'b18.stp')
INSTANCE_SET=B
mkdir -p Benchmarks/$INSTANCE_SET/$mytimestamp/ 
for instance in "${INSTANCES[@]}" 
do 
    for seed in {1..5}
    do
        Program/steiner Instances/$INSTANCE_SET/$instance -seed $seed > Benchmarks/$INSTANCE_SET/$mytimestamp/$instance-$seed.txt        
        cat Benchmarks/$INSTANCE_SET/$mytimestamp/$instance-$seed.txt | grep "Final" >> Benchmarks/$INSTANCE_SET/$mytimestamp/compiled-$instance.txt
        cat Benchmarks/$INSTANCE_SET/$mytimestamp/$instance-$seed.txt | grep "TIME" >> Benchmarks/$INSTANCE_SET/$mytimestamp/compiled-$instance.txt
    done
done

#Set C
INSTANCES=('c01.stp' 'c02.stp' 'c03.stp' 'c04.stp' 'c05.stp' 'c06.stp' 'c07.stp' 'c08.stp' 'c09.stp' 'c10.stp' 'c11.stp' 'c12.stp' 'c13.stp' 'c14.stp' 'c15.stp' 'c16.stp' 'c17.stp' 'c18.stp' 'c19.stp' 'c20.stp')
INSTANCE_SET=C
mkdir -p Benchmarks/$INSTANCE_SET/$mytimestamp/ 
for instance in "${INSTANCES[@]}" 
do 
    for seed in {1..5}
    do
        Program/steiner Instances/$INSTANCE_SET/$instance -seed $seed > Benchmarks/$INSTANCE_SET/$mytimestamp/$instance-$seed.txt        
        cat Benchmarks/$INSTANCE_SET/$mytimestamp/$instance-$seed.txt | grep "Final" >> Benchmarks/$INSTANCE_SET/$mytimestamp/compiled-$instance.txt
        cat Benchmarks/$INSTANCE_SET/$mytimestamp/$instance-$seed.txt | grep "TIME" >> Benchmarks/$INSTANCE_SET/$mytimestamp/compiled-$instance.txt
    done
done

#Set D
INSTANCES=('d01.stp' 'd02.stp' 'd03.stp' 'd04.stp' 'd05.stp' 'd06.stp' 'd07.stp' 'd08.stp' 'd09.stp' 'd10.stp' 'd11.stp' 'd12.stp' 'd13.stp' 'd14.stp' 'd15.stp' 'd16.stp' 'd17.stp' 'd18.stp' 'd19.stp' 'd20.stp')
INSTANCE_SET=D
mkdir -p Benchmarks/$INSTANCE_SET/$mytimestamp/ 
for instance in "${INSTANCES[@]}" 
do 
    for seed in {1..5}
    do
        Program/steiner Instances/$INSTANCE_SET/$instance -seed $seed > Benchmarks/$INSTANCE_SET/$mytimestamp/$instance-$seed.txt        
        cat Benchmarks/$INSTANCE_SET/$mytimestamp/$instance-$seed.txt | grep "Final" >> Benchmarks/$INSTANCE_SET/$mytimestamp/compiled-$instance.txt
        cat Benchmarks/$INSTANCE_SET/$mytimestamp/$instance-$seed.txt | grep "TIME" >> Benchmarks/$INSTANCE_SET/$mytimestamp/compiled-$instance.txt
    done
done

#Set E
INSTANCES=('e01.stp' 'e02.stp' 'e03.stp' 'e04.stp' 'e05.stp' 'e06.stp' 'e07.stp' 'e08.stp' 'e09.stp' 'e10.stp' 'e11.stp' 'e12.stp' 'e13.stp' 'e14.stp' 'e15.stp' 'e16.stp' 'e17.stp' 'e18.stp' 'e19.stp' 'e20.stp')
INSTANCE_SET=E
mkdir -p Benchmarks/$INSTANCE_SET/$mytimestamp/ 
for instance in "${INSTANCES[@]}" 
do 
    for seed in {1..5}
    do
        Program/steiner Instances/$INSTANCE_SET/$instance -seed $seed > Benchmarks/$INSTANCE_SET/$mytimestamp/$instance-$seed.txt        
        cat Benchmarks/$INSTANCE_SET/$mytimestamp/$instance-$seed.txt | grep "Final" >> Benchmarks/$INSTANCE_SET/$mytimestamp/compiled-$instance.txt
        cat Benchmarks/$INSTANCE_SET/$mytimestamp/$instance-$seed.txt | grep "TIME" >> Benchmarks/$INSTANCE_SET/$mytimestamp/compiled-$instance.txt
    done
done
