#ifndef POPULATION_H
#define POPULATION_H
#include <vector>
#include "Individual.h"
#include "Params.h"

typedef std::vector< Individual *> SubPopulation;
class Population
{
    Params *params;
public:
    int maxPopSize;
    SubPopulation population;
    Population(Params *params);
    void generateInitialPopulation();

    void addIndividual(Individual *newIndividual)
    {
        population.push_back(newIndividual);
        // population.push_back(newIndividual);
    }

};
#endif
