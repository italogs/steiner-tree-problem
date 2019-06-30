#ifndef LOCALSEARCH_H
#define LOCALSEARCH_H

#include <string>
#include <vector>
#include <set>
#include <fstream>
#include <iostream>
#include <algorithm> 
#include <time.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <queue>
#include <map>
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