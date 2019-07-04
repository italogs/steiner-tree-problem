#!/usr/bin/env bash
export PATH=/usr/bin:$PATH

cd Program
ls
rm steiner
rm *.o
make clean
make
cd ..

mytimestamp=`date "+%d-%m-%y-%H-%M-%S"`


# # Para experimentos extendidos
# echo "" > extended_experiments.txt
# Program/steiner Instances/B/b01.stp -seed 1 >> extended_experiments.txt 
# Program/steiner Instances/B/b13.stp -seed 1 >> extended_experiments.txt 
# Program/steiner Instances/C/c01.stp -seed 1 >> extended_experiments.txt 
# Program/steiner Instances/C/c06.stp -seed 1 >> extended_experiments.txt 


#Set B
INSTANCES=('b01.stp' 'b02.stp' 'b03.stp' 'b04.stp' 'b05.stp' 'b06.stp' 'b07.stp' 'b08.stp' 'b09.stp' 'b10.stp' 'b11.stp' 'b12.stp' 'b13.stp' 'b14.stp' 'b15.stp' 'b16.stp' 'b17.stp' 'b18.stp')
INSTANCE_SET=B
mkdir -p Benchmarks/$INSTANCE_SET/$mytimestamp/ 
for instance in "${INSTANCES[@]}" 
do 
    for seed in {1..5}
    do
        Program/steiner Instances/$INSTANCE_SET/$instance -seed $seed > Benchmarks/$INSTANCE_SET/$mytimestamp/$instance-$seed.txt        
        cat Benchmarks/$INSTANCE_SET/$mytimestamp/$instance-$seed.txt | grep "nbRemovedEdges;" >> Benchmarks/$INSTANCE_SET/$mytimestamp/compiled-$instance.txt
        cat Benchmarks/$INSTANCE_SET/$mytimestamp/$instance-$seed.txt | grep "nbRemovedVertices;" >> Benchmarks/$INSTANCE_SET/$mytimestamp/compiled-$instance.txt
        cat Benchmarks/$INSTANCE_SET/$mytimestamp/$instance-$seed.txt | grep "Kruskal-Pruning" >> Benchmarks/$INSTANCE_SET/$mytimestamp/compiled-$instance.txt
        cat Benchmarks/$INSTANCE_SET/$mytimestamp/$instance-$seed.txt | grep ">BEST" >> Benchmarks/$INSTANCE_SET/$mytimestamp/compiled-$instance.txt
    done
done


 #Set C
INSTANCES=('c01.stp' 'c02.stp' 'c03.stp' 'c04.stp' 'c05.stp' 'c06.stp' 'c07.stp' 'c08.stp' 'c09.stp' 'c10.stp' 'c11.stp' 'c12.stp' 'c13.stp' 'c14.stp' 'c15.stp') # 'c16.stp' 'c17.stp' 'c18.stp' 'c19.stp' 'c20.stp')
INSTANCE_SET=C
mkdir -p Benchmarks/$INSTANCE_SET/$mytimestamp/ 
for instance in "${INSTANCES[@]}" 
do 
    for seed in {1..5}
    do
        Program/steiner Instances/$INSTANCE_SET/$instance -seed $seed > Benchmarks/$INSTANCE_SET/$mytimestamp/$instance-$seed.txt        
        cat Benchmarks/$INSTANCE_SET/$mytimestamp/$instance-$seed.txt | grep "nbRemovedEdges;" >> Benchmarks/$INSTANCE_SET/$mytimestamp/compiled-$instance.txt
        cat Benchmarks/$INSTANCE_SET/$mytimestamp/$instance-$seed.txt | grep "nbRemovedVertices;" >> Benchmarks/$INSTANCE_SET/$mytimestamp/compiled-$instance.txt
        cat Benchmarks/$INSTANCE_SET/$mytimestamp/$instance-$seed.txt | grep "Kruskal-Pruning" >> Benchmarks/$INSTANCE_SET/$mytimestamp/compiled-$instance.txt
        cat Benchmarks/$INSTANCE_SET/$mytimestamp/$instance-$seed.txt | grep ">BEST" >> Benchmarks/$INSTANCE_SET/$mytimestamp/compiled-$instance.txt
    done
done



# # #Set B
# # INSTANCES=('b01.stp' 'b02.stp' 'b03.stp' 'b04.stp' 'b05.stp' 'b06.stp' 'b07.stp' 'b08.stp' 'b09.stp' 'b10.stp' 'b11.stp' 'b12.stp' 'b13.stp' 'b14.stp' 'b15.stp' 'b16.stp' 'b17.stp' 'b18.stp')
# # INSTANCE_SET=B
# # mkdir -p Benchmarks/$INSTANCE_SET/$mytimestamp/ 
# # for instance in "${INSTANCES[@]}" 
# # do 
# #     for seed in {1..5}
# #     do
# #         Program/steiner Instances/$INSTANCE_SET/$instance -seed $seed > Benchmarks/$INSTANCE_SET/$mytimestamp/$instance-$seed.txt        
# #         cat Benchmarks/$INSTANCE_SET/$mytimestamp/$instance-$seed.txt | grep "nbRemovedEdges;" >> Benchmarks/$INSTANCE_SET/$mytimestamp/compiled-$instance.txt
# #         cat Benchmarks/$INSTANCE_SET/$mytimestamp/$instance-$seed.txt | grep "nbRemovedVertices;" >> Benchmarks/$INSTANCE_SET/$mytimestamp/compiled-$instance.txt
# #         cat Benchmarks/$INSTANCE_SET/$mytimestamp/$instance-$seed.txt | grep ">BEST" >> Benchmarks/$INSTANCE_SET/$mytimestamp/compiled-$instance.txt
# #     done
# # done

# # #Set C
# # INSTANCES=('c01.stp' 'c02.stp' 'c03.stp' 'c04.stp' 'c05.stp') #'c06.stp' 'c07.stp' 'c08.stp' 'c09.stp' 'c10.stp' 'c11.stp' 'c12.stp' 'c13.stp' 'c14.stp' 'c15.stp' 'c16.stp' 'c17.stp' 'c18.stp' 'c19.stp' 'c20.stp')
# # INSTANCE_SET=C
# # mkdir -p Benchmarks/$INSTANCE_SET/$mytimestamp/ 
# # for instance in "${INSTANCES[@]}" 
# # do 
# #     for seed in {1..5}
# #     do
# #         Program/steiner Instances/$INSTANCE_SET/$instance -seed $seed > Benchmarks/$INSTANCE_SET/$mytimestamp/$instance-$seed.txt        
# #         cat Benchmarks/$INSTANCE_SET/$mytimestamp/$instance-$seed.txt | grep "nbRemovedEdges;" >> Benchmarks/$INSTANCE_SET/$mytimestamp/compiled-$instance.txt
# #         cat Benchmarks/$INSTANCE_SET/$mytimestamp/$instance-$seed.txt | grep "nbRemovedVertices;" >> Benchmarks/$INSTANCE_SET/$mytimestamp/compiled-$instance.txt
# #         cat Benchmarks/$INSTANCE_SET/$mytimestamp/$instance-$seed.txt | grep ">BEST" >> Benchmarks/$INSTANCE_SET/$mytimestamp/compiled-$instance.txt
# #     done
# # done

