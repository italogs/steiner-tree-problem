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

#define MY_EPSILON 0.00001

// Structure representing one node of the (orthogonal) decision tree or a leaf
class Node
{
public:
	int id;
	bool terminal;
	std::vector<Node *> adj_list;

	// To Do insert in sorted order
	void insert_adj(Node *node)
	{
		adj_list.push_back(node);
	}
};


class Edge
{
	public:
	int weight;
	Node *n1;
	Node *n2;
	Edge(Node *node1, Node *node2, int weight)
	{
		if (node1->id < node2->id)
		{
			this->n1 = node1;
			this->n2 = node2;			
		}
		else 
		{
			this->n1 = node2;
			this->n2 = node1;
		}
		this->weight = weight;
	}
};

class Graph
{
	public:
	std::vector<Node> node_list;
	std::vector<Edge> edge_list;
	std::vector<Node> terminal_list;

	void allocateNodes(int nbNodes)
	{
		node_list.resize(nbNodes);
		for (int i = 0 ; i < node_list.size() ; i++)
		{
			node_list[i].id = i;
		}
	}

	void setNodeAsTerminal(int node_id)
	{
		terminal_list.push_back(node_list[node_id-1]);
	}

	void insertEdge(int node_1, int node_2, int weight)
	{
		if (node_1 > node_2)
		{
			int temp  = node_1;
			node_1 = node_2;
			node_2 = temp;
		}
		printf("New edge: %d - %d: %d\n",node_1,node_2,weight);
		Edge new_edge(&node_list[ node_1 - 1], &node_list[ node_2 - 1], weight);
		edge_list.push_back(new_edge);
	}

};

class Params
{
public:

	/* GENERAL PARAMETERS */
	std::string pathToInstance ;	// Path to the instance
	std::string pathToSolution ;	// Path to the solution
	
	/* PARAMETERS OF THE ALGORITHM */
	int seed;						// Random seed (for randomized algorithms)

	/* INSTANCE INFORMATION */
	std::string instanceName;								// Name of the dataset

	/* TO MEASURE CPU TIME */
	clock_t startTime;				// Time when the algorithm started
	clock_t endTime;				// Time when the algorithm ended 

	Graph graph;

	/* CONSTRUCTOR */
	Params(std::string pathToInstance, std::string pathToSolution, int seed);
};
#endif

