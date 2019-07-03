#ifndef POPULATION_H
#define POPULATION_H

#include "Individual.h"
#include "Params.h"

typedef std::vector< Individual *> SubPopulation;
class Population
{
    Params *params;
public:
    int maxPopSize;
    SubPopulation subpopulation;
    Population(Params *params);
    void generateInitialPopulation();
    Individual *binaryTournament();
    Individual *getBestIndividual();
    void placeIndividual(Individual *individual);
    void addIndividual(Individual *newIndividual);
    void crossover(Individual *offspring);
    void mutation();
    void printAverageCost();
};
#endif
