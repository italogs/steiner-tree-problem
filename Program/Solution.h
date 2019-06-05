#ifndef SOLUTION_H
#define SOLUTION_H

#include <vector>
#include "Params.h"

// Structure representing one node of the (orthogonal) decision tree or a leaf
class Node
{

public:
	Params * params;										// Access to the problem and dataset parameters

	Node(Params * params):params(params)
	{
		
	}
};

class Solution
{

private:

	// Access to the problem and dataset parameters
	Params * params;

public:

	Solution(Params * params):params(params)
	{
	};
};
#endif
