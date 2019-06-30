#include "Params.h"
#include <queue>
#include <list>

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
		// reduceGraph();
	}
	else
	{
		std::cout << "----- IMPOSSIBLE TO OPEN DATASET: " << pathToInstance << std::endl;
	}
}


//not working. Need full revision
void Params::reduceGraph()
{
	// printf("adjList.size():1 %d\n",adjList.size());
	// bool need_another_iteration = true;
	// int nbRemovedArcs = 0;
	// std::vector<int> deleted_nodes;
    // while(need_another_iteration)
    // {
    //     need_another_iteration = false;
    //     for (int i = 0 ; i < adjList.size(); i++)
    //     {
    //         //Its a leaf and non-terminal
    //         if(adjList[i].size() == 1 && !terminalNodes[i])
    //         {
	// 			deleted_nodes.push_back(i);
    //             need_another_iteration = true;
    //             int source = i;
	// 			int destination = adjList[source][0].first;
    //             nbRemovedArcs++;
	// 			printf("(%d,%d);",source,destination);
    //             //Doing a symetric deletion (destination - source)
    //             for(int j = 0 ; j < adjList[destination].size(); j++)
    //             {
    //                 if(adjList[destination][j].first == source)
	// 				{
	// 					printf("(%d,%d);",destination,source);
	// 					adjList[destination].erase(adjList[destination].begin()+j);
	// 					break;
	// 				}
    //             }
	// 			//Removing edge of (source - destination)
	// 			adjList[source].clear();

	// 			// adjList.erase(adjList.begin() + source);
	// 			// terminalNodes.erase(terminalNodes.begin() + source);
	// 			break;
    //         }
    //     }
    // }


	// std::vector< std::vector< std::pair<int, int> > > adjListModified;
	// std::vector< int > terminalNodesModified;
	// for(int i = 0; i < adjList.size(); i++)
	// {
	// 	if(adjList[i].size() > 0)
	// 	{
	// 		adjListModified.push_back(adjList[i]);
	// 		terminalNodesModified.push_back(terminalNodes[i]);
	// 	}
	// 	adjList[i].clear();
	// }
	// adjList.clear();
	// terminalNodes.clear();
	// std::copy(adjList, adjListModified);
	// std::copy(terminalNodes, terminalNodesModified);
	// // adjList = adjListModified;
	// // terminalNodes = terminalNodesModified;
	// int id_edge = 0;
	// for(int i = 0; i < adjList.size(); i++)
	// {
	// 	printf("Degree %d: %d\n", i, adjList[i].size());
		
	// 	for(int j = 0 ; j < adjList[i].size() ; j++)
	// 	{
	// 		int source = i;
	// 		int destination = adjList[i][j].first;
	// 		int weight = adjList[i][j].second;
	// 		if(source > destination)
	// 			std::swap(source,destination);
	// 		auto result = edgeMap.insert( std::make_pair(std::make_pair(source,destination), std::make_pair(id_edge, weight)));
	// 		bool insertionPerformed = result.second;
	// 		if(insertionPerformed)
	// 			id_edge++;
	// 	}
		
		
	// }
	// printf("\n");
	// printf("NbNodes %d",adjList.size());

	// printf("nbEdges %d",adjList.size());
	
	

	


	// printf("\n");


	// printf("removedArcs %d",nbRemovedArcs);
	// printf("adjList.size():2 %d\n",adjList.size());
	// need_another_iteration = true;
	// printf("Deletando nós: ");
    // while(need_another_iteration)
    // {
    //     need_another_iteration = false;
	// 	for (int i = 0 ; i < adjList.size() ; i++)
	// 	{
	// 		//Its a leaf and non-terminal
	// 		if(adjList[i].size() == 0)
	// 		{
	// 			need_another_iteration = true;
	// 			if(terminalNodes[i])
	// 			{
	// 				printf("Opa.. isso nao pode acontecer\n");
	// 				exit(0);
	// 			}
	// 			printf("%d(%d),",i,adjList.size());
	// 			adjList.erase(adjList.begin()+i);
	// 			terminalNodes.erase(terminalNodes.begin()+i);
	// 			break;	
	// 		}
	// 	}
	// }

	// printf("\nadjList.size():3 %d\n",adjList.size());
	// need_another_iteration = true;
    // while(need_another_iteration)
    // {
    //     need_another_iteration = false;
	// 	for (int i = 0 ; i < adjList[i].size() ; i++)
	// 	{
	// 		//Its a leaf and non-terminal
	// 		if(adjList[i].size() == 0)
	// 		{
				
	// 				printf("Opa.. isso nao pode acontecer 2\n");
	// 				exit(0);
				
	// 		}

	// 		if(adjList[i].size() == 1 && !terminalNodes[i])
	// 		{
	// 			printf("Opa.. isso nao pode acontecer 3\n");
	// 				exit(0);
	// 		}
	// 	}
	// }


	

	// printf("adjList.size():4 %d\n",adjList.size());

	// int source = -1;
	// printf("BFS\n");
    // // If source is not provided, we take the first one that is part of the solution
    // if(source < 0)
    // {
    //     for(int i = 0; i < adjList.size(); i++)
    //     {
    //         if(adjList[i].size() > 0)
	// 		{

			
    //             source = i;
	// 			break;
	// 		}
    //     }
    // }
	// printf("root: %d,",source);
    // bool *visited = new bool[adjList.size()];
    // for(int i = 0; i < adjList.size(); i++) 
    //     visited[i] = false; 
    // // Create a queue for BFS 
    // std::list<int> queue; 
    // int current_node = source;
    // // Mark the current node as visited and enqueue it 
    // visited[current_node] = true; 
    // queue.push_back(current_node); 
    // int level = 0;
    // printf("%d\n",source);
    
    // while(!queue.empty()) 
    // { 
    //     // Dequeue a vertex from queue and print it 
    //     current_node = queue.front(); 
    //     queue.pop_front(); 
    //     printf("%d: ",current_node);
    //     for (auto it = adjList[current_node].begin(); it != adjList[current_node].end(); ++it) 
    //     {
    //         if (!visited[it->first]) 
    //         { 
    //             printf("%d,",it->first);
    //             visited[it->first] = true; 
    //             queue.push_back(it->first); 
    //         }
    //     }
    //     printf("\n",level);
    //     level++;
    // }

	// exit(0);
}