#include "Population.h"
#include <vector>
#include <set>
#include <unordered_set>
#include "Params.h"

Population::Population(Params *params): params(params)
{
    
}






void Population::generateInitialPopulation()
{
    population = std::vector< Individual *>(params->maxPopSize);
    std::set< std::pair< std::pair<int, int >, int > > edges_set;
    for(int source = 0; source < params->adjList.size(); source++)
    {
        int i = source;
        for(int target = 0; target < params->adjList[i].size(); target++)
        {
            int j = params->adjList[i][target].first;
            int weight = params->adjList[i][target].second;
            if(i > j)
                std::swap(i,j);
            
            auto result = edges_set.insert(std::make_pair(std::make_pair(i,j),weight));
        }
    }

    std::vector< std::pair< std::pair<int, int >, int > >  edges_vector(edges_set.begin(),edges_set.end());
    for(int i = 0 ; i < params->maxPopSize; i++)
    {
        std::random_shuffle(edges_vector.begin(),edges_vector.end());
        Individual *newIndividual = new Individual(params);
        for (const auto& elem: edges_vector) {
            newIndividual->insertEdgeIfFeasible(elem.first.first,elem.first.second,elem.second);
        }
        // newIndividual->BFSprint(-1);
        newIndividual->removeNonTerminalLeaves();
        // newIndividual->BFSprint(-1);
        newIndividual->calculateCost();
        this->addIndividual(newIndividual);



    }
}





