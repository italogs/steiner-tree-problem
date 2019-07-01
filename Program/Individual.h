#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H
#include "Params.h"
#include <list>
#include <vector>
#include <set>
#include <climits>
#include <cstdlib>

class Individual
{
	//Solution is just a subgraph
private:

	// Access to the problem and dataset parameters
	Params * params;
	std::vector<bool> visited;
public:
	int costSol;
	std::set<std::pair<int,int>> edgesSet;
	//At each node i, we have node[i] --> pair(destination,weight)
	std::vector< std::vector< std::pair<int, int> > > adjList;
	Individual(Params * params);
	bool insertEdgeIfFeasible(int source, int target, int weight);
	bool BFS(int source, int target);
	void BFSprint(int source);
	bool isFeasible();
	
	void printEdges();
	void removeNonTerminalLeaves();
	void eraseEdges();
	int getCost();
	void calculateCost();
	int getNbEdges();
	void setEdgesSet();
	int calculateDistance(Individual *individual);
	static void copy(Individual * destination, Individual * source);
};
#endif
