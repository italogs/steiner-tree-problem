#include "Commandline.h"
#include "Params.h"
#include "Solution.h"

int main(int argc, char *argv[])
{
	Commandline c(argc, argv);
	if (c.is_valid())
	{
		// Initialization of the problem data from the commandline
		Params params(c.get_path_to_instance(), c.get_path_to_solution(), c.get_seed());

		// Initialization of a solution structure
		// Solution solution(&params);

		// Run the greedy algorithm 
		std::cout << "----- STARTING ALGORITHM" << std::endl;
		params.startTime = clock();
		
		

		params.endTime = clock();
		std::cout << "----- ALGORITHM COMPLETED IN " << (params.endTime - params.startTime) / (double)CLOCKS_PER_SEC << "(s)" << std::endl;
		
		// Printing the solution and exporting statistics (also export results into a file)
		std::cout << "----- END OF ALGORITHM" << std::endl;
	}
	return 0;
}
