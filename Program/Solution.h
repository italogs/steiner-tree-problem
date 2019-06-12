#ifndef SOLUTION_H
#define SOLUTION_H

#include <vector>
#include "Params.h"

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
