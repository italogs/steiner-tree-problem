#ifndef LOCALSEARCH_H
#define LOCALSEARCH_H

#include "Params.h"
#include "Individual.h"

#define MY_EPSILON 0.00001

class LocalSearch
{
    Params *params;
    Individual *offspring;
public:
    void nodeBasedNeighborhood();
    void run(Individual *offspring);
    bool static sortAscEdges(std::pair<std::pair<int,int>,int> i, std::pair<std::pair<int,int>,int> j);
    LocalSearch(Params *params);
};
#endif