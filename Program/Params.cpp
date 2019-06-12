#include "Params.h"

Params::Params(std::string pathToInstance, std::string pathToSolution, int seed) : seed(seed), pathToInstance(pathToInstance), pathToSolution(pathToSolution)
{
	// Initializing random number generator here (if you have nondeterministic components)
	std::srand(seed);
	std::cout << "----- INITIALIZING ALGORITHM WITH SEED: " << seed << std::endl;
	std::ifstream inputFile(pathToInstance.c_str());
	std::cout << "Instance: " << pathToInstance.c_str() << std::endl;
	if (inputFile.is_open())
	{
		std::string file_header;
		getline (inputFile, file_header);
		std::string s1, s2, s3, s4;
		std::string::size_type sz;   // alias of size_t
		while(!inputFile.eof())
		{
			inputFile >> s1;
			if(s1.size() == 0)
				continue;
			inputFile >> s2;
			if(s1 == "SECTION" && s2 == "Comment")
			{
				getline (inputFile, file_header);
				while (file_header != "END")
				{
					getline (inputFile, file_header);
				}
			}

			 else if(s1 == "SECTION" && s2 == "Graph")
			{
				// Collecting nb of nodes
				inputFile >> s1 >> s2;
				int nbNodes = std::stoi(s2,&sz);
				// Collecting nb of edges
				inputFile >> s1 >> s2;
				// int nbEdges = std::stoi(s2,&sz);
				// printf("NbNodes %d nbEdges %d\n", nbNodes , nbEdges);
				graph.allocateNodes(nbNodes);
				inputFile >> s1 >> s2 >> s3 >> s4;
				while(s1 != "END")
				{
					//Format: E node1 node2 weight
					// int int_s1 = std::stoi(s1);
					int int_s2 = std::stoi(s2,&sz);
					int int_s3 = std::stoi(s3,&sz);
					int int_s4 = std::stoi(s4,&sz);
					graph.insertEdge(int_s2,int_s3,int_s4);
					inputFile >> s1;
					if(s1 == "END")
						break;
					inputFile >>  s2 >> s3 >> s4;
				}
			}

			else if(s1 == "SECTION" && s2 == "Terminals")
			{
				// Terminals *
				inputFile >> s1 >> s2;
				//Format T *
				inputFile >> s1 >> s2;
				while(s1 != "END")
				{
					int terminal_id = std::stoi(s2);
					//Format T *
					graph.setNodeAsTerminal(terminal_id);
					inputFile >> s1 >> s2;
				}
			}
		}
		std::cout << "----- INSTANCE WAS READ" << std::endl;
	}
	else
	{
		std::cout << "----- IMPOSSIBLE TO OPEN DATASET: " << pathToInstance << std::endl;
	}
}