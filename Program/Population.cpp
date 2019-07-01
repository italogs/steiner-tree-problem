#include <vector>
#include <set>
#include <unordered_set>

#include "Population.h"
#include "Params.h"
#include "Individual.h"

Population::Population(Params *params): params(params)
{
}


void Population::placeIndividual(Individual *individual)
{
    int worstIndividual = 0;
    for(int i = 0; i < subpopulation.size(); i++ )
    {
        //If already exists in population, we dont insert it
        if(subpopulation[i]->calculateDistance(individual) == 0)
            return;
        if(subpopulation[worstIndividual]->getCost() < subpopulation[i]->getCost())
            worstIndividual = i;
    }
    Individual::copy(subpopulation[worstIndividual], individual);
}

void Population::crossover(Individual *offspring)
{
    Individual *parent1 = this->binaryTournament();
    Individual *parent2 = this->binaryTournament();
    std::vector<int> edgeIncidenceVectorParent1(params->getNbEdges(),0), edgeIncidenceVectorParent2(params->getNbEdges(),0),edgeIncidenceVectorOffspring(params->getNbEdges(),0);

    //making a incidence vector for cutting
    int source, destination;
    for(int i = 0 ; i < parent1->adjList.size() ; i++)
    {
        for(int j = 0 ; j < parent1->adjList[i].size(); j++)
        {
            source = i;
            destination = parent1->adjList[i][j].first;
            if(destination < source)
                std::swap(source,destination);
            int id = params->edgeMap[std::make_pair(source,destination)].first;
            edgeIncidenceVectorParent1[id] = 1;
        }
    }

    for(int i = 0 ; i < parent2->adjList.size() ; i++)
    {
        for(int j = 0 ; j < parent2->adjList[i].size(); j++)
        {
            source = i;
            destination = parent2->adjList[i][j].first;
            if(destination < source)
                std::swap(source,destination);
            int id = params->edgeMap[std::make_pair(source,destination)].first;
            edgeIncidenceVectorParent2[id] = 1;
        }
    }

    //obtaining cutting point
    //Cut cannot be start neither end
    offspring->eraseEdges();

    int cut_1 = std::rand() % (params->getNbEdges() - 1) + 1;
    int cut_2 = std::rand() % (params->getNbEdges() - 1) + 1;
    if(cut_1 > cut_2)
        std::swap(cut_1,cut_2);
    // printf("cut %d\n",cut);
    for (int i = 0; i < cut_1 ; i++)
        edgeIncidenceVectorOffspring[i] = edgeIncidenceVectorParent1[i];
    for (int i = cut_1; i < cut_2 ; i++)
        edgeIncidenceVectorOffspring[i] = edgeIncidenceVectorParent2[i];
    for (int i = cut_2; i < edgeIncidenceVectorOffspring.size() ; i++)
        edgeIncidenceVectorOffspring[i] = edgeIncidenceVectorParent1[i];

    int id;
    //Inserting edges from parents
    //If an edge creates a cycle, skip it!
    std::vector<std::pair<int,int>> edgesVector;
    for (auto &it: params->edgeMap)
    {
        id = it.second.first;
        if(edgeIncidenceVectorOffspring[id] > 0)
            offspring->insertEdgeIfFeasible(it.first.first,it.first.second,it.second.second);
        edgesVector.push_back(std::make_pair(it.first.first,it.first.second));
    }

    std::random_shuffle(edgesVector.begin(),edgesVector.end());

    for (int i = 0 ; i < edgesVector.size(); i++)
    {
        std::pair<int,int> edge_info = params->edgeMap[edgesVector[i]];
        offspring->insertEdgeIfFeasible(edgesVector[i].first,edgesVector[i].second,edge_info.second);   
    }
    offspring->removeNonTerminalLeaves();
    offspring->calculateCost();
}

Individual *Population::getBestIndividual()
{
    Individual *best = subpopulation[0];
    for (int i = 1 ; i < subpopulation.size(); i++)
        if(subpopulation[i]->getCost() < best->getCost())
            best = subpopulation[i];
    return best;
}

Individual *Population::binaryTournament()
{
    int pos1 = std::rand() % subpopulation.size();
    int pos2 = std::rand() % subpopulation.size();
    Individual *individual1 = subpopulation[pos1], *individual2 = individual2 = subpopulation[pos2];    
    return  (individual1->getCost() < individual2->getCost()) ? individual1: individual2;  
}

void Population::addIndividual(Individual *newIndividual)
{
    subpopulation.push_back(newIndividual);
}

void Population::generateInitialPopulation()
{
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
            
            edges_set.insert(std::make_pair(std::make_pair(i,j),weight));
        }
    }
    std::vector< std::pair< std::pair<int, int >, int > >  edges_vector(edges_set.begin(),edges_set.end());
    for(int i = 0 ; i < params->maxPopSize; i++)
    {
        std::random_shuffle(edges_vector.begin(),edges_vector.end());
        Individual *newIndividual = new Individual(params);
        for (const auto& elem: edges_vector) {
            newIndividual->insertEdgeIfFeasible(elem.first.first, elem.first.second, elem.second);
        }
        newIndividual->removeNonTerminalLeaves();
        newIndividual->calculateCost();
        this->addIndividual(newIndividual);
    }
}





