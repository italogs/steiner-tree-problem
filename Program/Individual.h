#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include <vector>
#include "Params.h"

class Individual
{
	//Solution is just a subgraph
private:

	// Access to the problem and dataset parameters
	Params * params;
	std::vector< std::vector< std::pair<int, int> > > adjList;
	int costSol;

public:
	Individual(Params * params);
	void insertEdgeIfFeasible(int source, int target, int weight);
	bool BFS(int source, int target);
	void BFSprint(int source);
	void removeNonTerminalLeaves();
	void calculateCost();
	static void copy(Individual * destination, Individual * source);
};
#endif
