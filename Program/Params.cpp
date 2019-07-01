#include "Params.h"
#include <queue>
#include <list>
#include "Individual.h"

void Params::PrintGraph()
{
	printf("Graph:\n");
	for (int i = 0 ; i < adjList.size(); i++)
	{
		printf("%d: ", i);
		for(int j = 0 ; j < adjList[i].size() ; j++)
			printf("%d (w: %d), ", adjList[i][j].first, adjList[i][j].second);
		printf("\n");
	}
	printf("Terminal nodes (%d): ",terminalNodes.size());
	for(int i = 0; i < terminalNodes.size() ; i++)
	{
		if(terminalNodes[i])
			printf("%d, ",i);
	}
	printf("\n");
}

int Params::getEdgeWeight(int node1, int node2)
{
	for(int i = 0 ; i < adjList[node1].size(); i++)
		if(adjList[node1][i].first == node2)
			return adjList[node1][i].second;
	throw std::string("Edge not found.\n");
}


int Params::getNbEdges()
{	
	return this->edgeMap.size();
}

Params::Params(std::string pathToInstance, std::string pathToSolution, int seed) : seed(seed), pathToInstance(pathToInstance), pathToSolution(pathToSolution)
{
	// Initializing random number generator here (if you have nondeterministic components)
	std::srand(seed);
	this->maxPopSize = 20;
	
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
				for(int i = 0; i < nbNodes; i++)
				{
					// Create a vector to represent a row, and add it to the adjList.
					std::vector<std::pair<int, int> > row;
					adjList.push_back(row);
					terminalNodes.push_back(0);
				}
				
				inputFile >> s1 >> s2 >> s3 >> s4;
				int id_edge = 0;
				while(s1 != "END")
				{
					//Format: E node1 node2 weight
					int source = std::stoi(s2,&sz);
					
					int destination = std::stoi(s3,&sz);
					
					int weight = std::stoi(s4,&sz);

					source--;
					destination--;
					adjList[source].push_back(std::make_pair(destination,weight));
					adjList[destination].push_back(std::make_pair(source,weight));
					if(source > destination)
						std::swap(source,destination);
					auto result = edgeMap.insert( std::make_pair(std::make_pair(source,destination), std::make_pair(id_edge, weight)));
					bool insertionPerformed = result.second;
					if(insertionPerformed)
						id_edge++;


					inputFile >> s1;
					if(s1 == "END")
						break;
					inputFile >> s2 >> s3 >> s4;
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
					terminal_id--;
					terminalNodes[terminal_id] = 1;
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

int Params::getNbNodes()
{
	return this->adjList.size();
}
