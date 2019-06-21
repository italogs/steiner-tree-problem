#include "Individual.h"
#include <list>
#include <queue>

void Individual::copy(Individual * destination, Individual * source)
{

}


void Individual::insertEdgeIfFeasible(int source, int target, int weight)
{
    if(!this->BFS(source,target))
    {
        adjList[source].push_back(std::make_pair(target,weight));
        adjList[target].push_back(std::make_pair(source,weight));
    }
}

//Returns true if target is reachable
bool Individual::BFS(int source, int target)
{
    bool *visited = new bool[adjList.size()];
    for(int i = 0; i < adjList.size(); i++) 
        visited[i] = false; 
    // Create a queue for BFS 
    std::list<int> queue; 
    int current_node = source;
    // Mark the current node as visited and enqueue it 
    visited[current_node] = true; 
    queue.push_back(current_node); 

    while(!queue.empty()) 
    { 
        // Dequeue a vertex from queue and print it 
        current_node = queue.front(); 
        queue.pop_front(); 

        for (auto it = adjList[current_node].begin(); it != adjList[current_node].end(); ++it) 
        {
            if (!visited[it->first]) 
            { 
                if(target == it->first)
                    return true;
                visited[it->first] = true; 
                queue.push_back(it->first); 
            } 
        }
    }
    return false;
}

void Individual::removeNonTerminalLeaves()
{
    bool need_another_iteration = true;
    while(need_another_iteration)
    {
        need_another_iteration = false;
        for (int i = 0 ; i < adjList.size(); i++)
        {
            //Its a leaf and non-terminal
            if(adjList[i].size() == 1 && !params->terminalNodes[i])
            {
                
                need_another_iteration = true;
                int node = adjList[i][0].first;
                //Removing
                adjList[i].erase(adjList[i].begin());
                //Doing a symetric deletion
                for(int j = 0 ; j < adjList[node].size(); j++)
                {
                    if(adjList[node][j].first == i)
                        adjList[node].erase(adjList[node].begin()+j);
                }
            }
        }
    }
}

void Individual::calculateCost()
{
    std::set< std::pair< std::pair<int, int >, int > > edges_set;
    for(int source = 0; source < adjList.size(); source++)
    {
        
        for(int target = 0; target < adjList[source].size(); target++)
        {
            int i = source;
            int j = adjList[source][target].first;
            int weight = adjList[source][target].second;
            if(i > j)
                std::swap(i,j);
            
            auto result = edges_set.insert(std::make_pair(std::make_pair(i,j),weight));
        }
    }
    //solution's edges
    for (const auto& elem: edges_set)
        costSol += elem.second;
}

void Individual::BFSprint(int source)
{
    printf("BFS\n");
    // If source is not provided, we take the first one that is part of the solution
    if(source < 0)
    {
        for(int i = 0; i < adjList.size(); i++)
        {
            if(adjList[i].size() > 0)
                source = i;
        }
    }
    bool *visited = new bool[adjList.size()];
    for(int i = 0; i < adjList.size(); i++) 
        visited[i] = false; 
    // Create a queue for BFS 
    std::list<int> queue; 
    int current_node = source;
    // Mark the current node as visited and enqueue it 
    visited[current_node] = true; 
    queue.push_back(current_node); 
    int level = 0;
    printf("%d\n",source);
    
    while(!queue.empty()) 
    { 
        // Dequeue a vertex from queue and print it 
        current_node = queue.front(); 
        queue.pop_front(); 
        printf("%d: ",current_node);
        for (auto it = adjList[current_node].begin(); it != adjList[current_node].end(); ++it) 
        {
            if (!visited[it->first]) 
            { 
                printf("%d,",it->first);
                visited[it->first] = true; 
                queue.push_back(it->first); 
            }
        }
        printf("\n",level);
        level++;
    }
}

Individual::Individual(Params * params): params(params)
{
    costSol = 0;
    adjList = std::vector< std::vector< std::pair<int, int> > >(params->adjList.size());
};