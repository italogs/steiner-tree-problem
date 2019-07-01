#include "Individual.h"
#include "LocalSearch.h"
#include <list>
#include <queue>
#include <set>
#include <climits>
#include <cstdlib>
#include <stack>

struct DisjointSets ;
LocalSearch::LocalSearch(Params *params): params(params)
{

}


void LocalSearch::run(Individual *offspring)
{
    this->offspring = offspring;
    nodeBasedNeighborhood();
}


void LocalSearch::nodeBasedNeighborhood()
{
    bool found_improvement = true;
    while(found_improvement)
    {
        found_improvement = false;
        std::set<int> terminal_nodes;
        std::set<int> out_steiner_nodes;
        std::set<int> in_steiner_nodes;
        for(int i = 0; i < offspring->adjList.size();i++)
        {
            //this node is part of the solution
            if(offspring->adjList[i].size() > 0 && !params->terminalNodes[i])
                in_steiner_nodes.insert(i);
            else if(params->terminalNodes[i])
                terminal_nodes.insert(i);
            else if(offspring->adjList[i].size() == 0)
                out_steiner_nodes.insert(i);
        }

        Individual lsIndividual(this->params);
        Individual bestLSIndividual(this->params);
        Individual::copy(&bestLSIndividual,offspring);
        
        std::vector<int> candidate_steiner_nodes(in_steiner_nodes.begin(), in_steiner_nodes.end());
        candidate_steiner_nodes.insert(candidate_steiner_nodes.begin(),out_steiner_nodes.begin(),out_steiner_nodes.end());
        std::random_shuffle(candidate_steiner_nodes.begin(), candidate_steiner_nodes.end());
        for(int i = 0 ; i < candidate_steiner_nodes.size(); i++)
        {
            int candidate_node = candidate_steiner_nodes[i];
            //Insert candidate
            if(out_steiner_nodes.find(candidate_node) == out_steiner_nodes.end())
            {
                lsIndividual.eraseEdges();
                int min_edges = 0;
                //Check in graph if the candidate node has at least 2 edges in in_steiner_nodes
                for(int j = 0; j < params->adjList[candidate_node].size(); j++)
                {
                    int k = params->adjList[candidate_node][j].first;
                    if(offspring->adjList[k].size() > 0 )
                        min_edges++;
                    if(min_edges > 1)
                        break;
                }

                if (min_edges < 2) //Infeasible insertion
                    continue;
                else
                {
                    lsIndividual.eraseEdges();
                    // copying solution
                    for(int j = 0; j < offspring->adjList.size(); j++)
                        lsIndividual.adjList[j] = offspring->adjList[j];
                    
                    //including node u and all edges (u,v) if v is a steiner node in offspring
                    for(int j = 0; j < params->adjList[candidate_node].size(); j++)
                    {
                        int k = params->adjList[candidate_node][j].first;
                        if(offspring->adjList[k].size() > 0)
                        {
                            int weight = params->adjList[candidate_node][j].second;
                            lsIndividual.adjList[k].push_back(std::make_pair(candidate_node, weight));
                            lsIndividual.adjList[candidate_node].push_back(std::make_pair(k,weight));
                        }
                    }

                    lsIndividual.setEdgesSet();

                    //Sort edges
                    std::vector<std::pair<std::pair<int,int>,int>> edges_vector;

                    for(auto &edge : lsIndividual.edgesSet)
                    {
                        std::pair<int,int> edge_info = params->edgeMap[edge];
                        int weight = edge_info.second;
                        int source = edge.first;
                        int destination = edge.second;
                        edges_vector.push_back(std::make_pair(std::make_pair(source, destination), weight));
                    }
                    std::sort(edges_vector.begin(),edges_vector.end(), LocalSearch::sortAscEdges);
                    std::vector<std::pair<std::pair<int,int>,int>>::iterator it;
                    lsIndividual.eraseEdges();
                    for (it = edges_vector.begin(); it!=edges_vector.end(); it++) 
                    {
                        int u = it->first.first; 
                        int v = it->first.second; 
                        int weight = it->second;
                        lsIndividual.insertEdgeIfFeasible(u,v,weight);
                    }
                    lsIndividual.removeNonTerminalLeaves();
                    lsIndividual.calculateCost();
                    if(lsIndividual.getCost() < bestLSIndividual.getCost())
                    {
                        found_improvement = true;
                        Individual::copy(&bestLSIndividual,&lsIndividual);
                    }
                }   
            } 
            else // Delete candidate
            {
                // // candidate_node
                lsIndividual.eraseEdges();
                for(int j = 0; j < offspring->adjList.size(); j++)
                    lsIndividual.adjList[j] = offspring->adjList[j];

                //We eliminate candidate_node from the graph. 
                //In other words, we remove all edges adjacent to candidate_node
                for (int i = 0 ; i < lsIndividual.adjList[candidate_node].size(); i++)
                {//For each v adjacent to candidate_node, we eliminate its symetric
                    int destination = lsIndividual.adjList[candidate_node][i].first;
                    for (int j = 0 ; j < lsIndividual.adjList[destination].size(); j++)
                    {
                        if(lsIndividual.adjList[destination][j].first = candidate_node)
                        {
                            lsIndividual.adjList[destination].erase(lsIndividual.adjList[destination].begin() + j);
                            break;
                        }
                    }
                }
                lsIndividual.adjList[candidate_node].clear();                
                //Insert edges (u,v), where u is adjacent to candidate_node and v is in the graph
                for(int i = 0; i < params->adjList[candidate_node].size(); i++)
                {
                    int u = params->adjList[candidate_node][i].first;
                    for (int j = 0 ; j < params->adjList[u].size() ; j++)
                    {
                        int v = params->adjList[u][j].first;
                        int weight = params->adjList[u][j].second;
                        //If v its in the graph
                        if(lsIndividual.adjList[v].size() > 0)
                        {
                            lsIndividual.adjList[u].push_back(std::make_pair(v,weight));
					        lsIndividual.adjList[v].push_back(std::make_pair(u,weight));
                        }
                    }
                }
                lsIndividual.setEdgesSet();

                std::vector<std::pair<std::pair<int,int>,int>> edges_vector;
                for(auto &edge : lsIndividual.edgesSet)
                {
                    std::pair<int,int> edge_info = params->edgeMap[edge];
                    int weight = edge_info.second;
                    int source = edge.first;
                    int destination = edge.second;
                    edges_vector.push_back(std::make_pair(std::make_pair(source, destination), weight));
                }
                std::sort(edges_vector.begin(),edges_vector.end(), LocalSearch::sortAscEdges);
                lsIndividual.eraseEdges();
                std::vector<std::pair<std::pair<int,int>,int>>::iterator it;
                for (it = edges_vector.begin(); it!=edges_vector.end(); it++) 
                {
                    int u = it->first.first; 
                    int v = it->first.second; 
                    int weight = it->second;
                    lsIndividual.insertEdgeIfFeasible(u,v,weight);
                }
                lsIndividual.removeNonTerminalLeaves();
                lsIndividual.calculateCost();
                if(lsIndividual.isFeasible() && lsIndividual.getCost() < bestLSIndividual.getCost())
                {
                    found_improvement = true;
                    Individual::copy(&bestLSIndividual,&lsIndividual);
                }   
            }
        }
        if(bestLSIndividual.getCost() < offspring->getCost())
            Individual::copy(offspring,&bestLSIndividual);
    }
}

bool LocalSearch::sortAscEdges( std::pair< std::pair<int,int> ,int > i, std::pair< std::pair< int,int > , int > j)
{
    return ( i.second < j.second );
}

