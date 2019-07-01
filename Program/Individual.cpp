#include "Individual.h"
#include <list>
#include <queue>
#include <set>
#include <climits>
#include <cstdlib>

void Individual::copy(Individual * destination, Individual * source)
{
    destination->adjList = source->adjList;
    destination->costSol = source->costSol;
}

void Individual::setEdgesSet()
{
    edgesSet.clear();
    int source, destination;
    for(int i = 0 ; i < adjList.size(); i++ ) 
    {
        for(int j = 0 ; j < adjList[i].size(); j++)
        {
            source = i;
            destination = adjList[i][j].first;
            std::pair<int,int> edge;
            if(source > destination)
                std::swap(source,destination);
            edge = std::make_pair(source, destination);
            edgesSet.insert(edge);
        }
    }
}

//O(m log m)
//Distance == 0 means that both solutions are the same
int Individual::calculateDistance(Individual *individual)
{
    int distance = 0;
    for(auto &edge : this->edgesSet)
        if(individual->edgesSet.find(edge) == individual->edgesSet.end())
            distance++;
    distance += std::abs( (int)(individual->edgesSet.size() -  this->edgesSet.size()));
    return distance;
}

int Individual::getNbEdges()
{
    return (int)edgesSet.size();
}

void Individual::eraseEdges()
{
    for(int i = 0; i < adjList.size(); i++) 
        adjList[i].clear();
    edgesSet.clear();
}

int Individual::getCost()
{
    return this->costSol;
}

bool Individual::insertEdgeIfFeasible(int source, int target, int weight)
{
    //It creates cycle? If so, don't insert
    if(!this->BFS(source,target))
    {
        adjList[source].push_back(std::make_pair(target,weight));
        adjList[target].push_back(std::make_pair(source,weight));
        if(source > target)
            std::swap(source, target);
        edgesSet.insert({source, target});
        return true;
    }
    return false;
}

bool Individual::isFeasible()
{
    //Do a BFS and check if graph is connected
    int source = -1;

    bool *visited = new bool[adjList.size()];
    for(int i = 0; i < adjList.size(); i++) 
    {
        if(adjList[i].size() > 0 && source < 0)
            source = i;
        visited[i] = false; 
    }

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
                visited[it->first] = true; 
                queue.push_back(it->first); 
            }
        }
    }

    for(int i = 0; i < adjList.size(); i++)
        if(adjList[i].size() > 0 && !visited[i])
            return false;

    return true;
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

bool Individual::DFS(int source)
{
    if(source < 0)
    {
        for(int i = 0; adjList.size();i++)
        {
            if(adjList[i].size() > 0)
            {
                source = i;
                break;
            }
        }
    }
    visited = std::vector<int>(adjList.size(),-1);
    cycleDetected = false;
    DFSDetectCycle(source);
    return cycleDetected;
}

//Returns true if target is reachable
void Individual::DFSDetectCycle(int source)
{
    visited[source] = 0; 
    for (auto it = adjList[source].begin(); it != adjList[source].end(); ++it) 
    {
         if (!visited[it->first]) 
        { 
            DFSDetectCycle(it->first);
        } 
        else if(visited[source] == 0)
        {
            cycleDetected = true;
            return;
        }
        if(cycleDetected)
            return;
    }
}

void Individual::removeNonTerminalLeaves()
{
    bool need_another_iteration = true;
    while(need_another_iteration)
    {
        need_another_iteration = false;
        for (int i = 0 ; i < adjList.size(); i++)
        {
            //It's a leaf and non-terminal
            if(adjList[i].size() == 1 && params->terminalNodes[i] == 0)
            {
                need_another_iteration = true;
                int adj_node = adjList[i][0].first;
                for(int j = 0 ; j < adjList[adj_node].size(); j++)
                {
                    if(adjList[adj_node][j].first == i)
                    {
                        adjList[adj_node].erase(adjList[adj_node].begin() + j);
                        break;
                    }
                }
                adjList[i].clear();
                break;
            }
        }
    }
}

void Individual::calculateCost()
{
    setEdgesSet();
    std::set< std::pair< std::pair<int, int >, int > > edges_set;
    costSol = 0;
    for(int source = 0; source < adjList.size(); source++)
    {
        for(int target = 0; target < adjList[source].size(); target++)
        {
            int i = source;
            int j = adjList[source][target].first;
            int weight = adjList[source][target].second;
            if(i > j)
                std::swap(i,j);
            
            edges_set.insert(std::make_pair(std::make_pair(i,j),weight));
        }
    }
    //solution's edges
    for (const auto& elem: edges_set)
        costSol += elem.second;
}

void Individual::printEdges()
{
    printf("Printing edges:\n");
    int source, destination;
    for(int i = 0 ; i < adjList.size(); i++ ) 
    {
        for(int j = 0 ; j < adjList[i].size(); j++)
        {
            source = i;
            destination = adjList[i][j].first;
            if(source < destination)
            {
                printf("(%d,%d)\n",source,destination);
            }
        }
    }
    printf("\n");
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
            {   
                source = i;
                break;
            }
                
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
    costSol = INT_MAX;
    adjList = std::vector< std::vector< std::pair<int, int> > >(params->getNbNodes());
};