#include "Individual.h"
#include "LocalSearch.h"
#include <list>
#include <queue>
#include <set>
#include <climits>
#include <cstdlib>
#include <stack>


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
                    if(offspring->adjList[k].size() > 0 )
                    {
                        int weight = params->adjList[candidate_node][j].second;
                        lsIndividual.adjList[k].push_back(std::make_pair(candidate_node, weight));
                        lsIndividual.adjList[candidate_node].push_back(std::make_pair(k,weight));
                    }
                }

                //Run kruskal's algorithm
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
                printf("Before sort");
                for(int i = 0 ; i < edges_vector.size() ; i++)
                    printf("(%d,%d):%d, ",edges_vector[i].first.first,edges_vector[i].first.second,edges_vector[i].second);
                printf("\n");
                std::sort(edges_vector.begin(),edges_vector.end(), LocalSearch::sortAscEdges);
                printf("after sort");
                for(int i = 0 ; i < edges_vector.size() ; i++)
                    printf("(%d,%d):%d, ",edges_vector[i].first.first,edges_vector[i].first.second,edges_vector[i].second);
                lsIndividual.DFS(-1);
                
                exit(0);
            }
        } 
        else // Delete candidate
        {
            
        }
    }
}

// bool hasCycle(Individual *ind, int start_node) {
    
//     std::stack<int> frontier;
//     frontier.push(start_node);

//     std::set<int> explored;

//     while(frontier.size() != 0)
//     {
//         int current_node = frontier.top();
//         frontier.pop();

//         if( explored.find(current_node) != explored.end())
//             continue;
        
//         for(int i = 0; i < ind->adjList[current_node].size(); i++)
//             frontier.push(ind->adjList[current_node][i].first);
//         explored.insert(current_node);
//     }



//     frontier = new Stack()
//     frontier.push(start_node)
//     explored = new Set()
//     while frontier is not empty:
//         current_node = frontier.pop()
//         if current_node in explored: continue
//         if current_node == end_node: return success
        
//         for neighbor in graph.get_neigbhors(current_node):
//             frontier.push(neighbor)
//         explored.add(current_node)
// }


bool LocalSearch::sortAscEdges( std::pair< std::pair<int,int> ,int > i, std::pair< std::pair< int,int > , int > j)
{
    return ( i.second < j.second );
}