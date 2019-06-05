#include "Params.h"

Params::Params(std::string pathToInstance, std::string pathToSolution, int seed) : seed(seed), pathToInstance(pathToInstance), pathToSolution(pathToSolution)
{
	// Initializing random number generator here (if you have nondeterministic components)
	std::srand(seed);
	std::cout << "----- INITIALIZING ALGORITHM WITH SEED: " << seed << std::endl;

	std::ifstream inputFile(pathToInstance.c_str());
	if (inputFile.is_open())
	{
	}
	else
		std::cout << "----- IMPOSSIBLE TO OPEN DATASET: " << pathToInstance << std::endl;
}