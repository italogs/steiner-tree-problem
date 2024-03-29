#ifndef PARAMS_H
#define PARAMS_H

#include <vector>
#include <set>
#include <iostream>
#include <queue>
#include <fstream>
#include <map>
#include <climits>
#include <algorithm> 
#include <time.h>
#include <math.h>

#define MY_EPSILON 0.00001

class Params
{
public:

	/* GENERAL PARAMETERS */
	std::string pathToInstance ;	// Path to the instance
	std::string pathToSolution ;	// Path to the solution
	
	/* PARAMETERS OF THE ALGORITHM */
	int seed;						// Random seed (for randomized algorithms)
	int maxPopSize;
	int mutation_rate;
	/* INSTANCE INFORMATION */
	std::string instanceName;								// Name of the dataset

	/* TO MEASURE CPU TIME */
	clock_t startTime;				// Time when the algorithm started
	clock_t endTime;				// Time when the algorithm ended 

	std::vector< std::vector< std::pair<int, int> > > adjList;

	//index is pair (i,j); value is pair(id_edge,weight)
	std::map< std::pair<int, int>, std::pair<int,int> > edgeMap;
	std::vector< int > terminalNodes;

	/* CONSTRUCTOR */
	Params(std::string pathToInstance, std::string pathToSolution, int seed);
	void PrintGraph();
	int getEdgeWeight(int node1, int node2);
	int getNbEdges();
	int getNbNodes();
};
#endif