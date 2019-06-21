#ifndef PARAMS_H
#define PARAMS_H

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

	/* INSTANCE INFORMATION */
	std::string instanceName;								// Name of the dataset

	/* TO MEASURE CPU TIME */
	clock_t startTime;				// Time when the algorithm started
	clock_t endTime;				// Time when the algorithm ended 

	std::vector< std::vector< std::pair<int, int> > > adjList;
	std::vector< int > terminalNodes;

	/* CONSTRUCTOR */
	Params(std::string pathToInstance, std::string pathToSolution, int seed);
	void PrintGraph();

	int getEdgeWeight(int node1, int node2)
	{
		for(int i = 0 ; i < adjList[node1].size(); i++)
			if(adjList[node1][i].first == node2)
				return adjList[node1][i].second;
		throw std::string("Edge not found.\n");
		return -1;
	}

};
#endif