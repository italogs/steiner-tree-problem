#include "Commandline.h"
#include "Params.h"
#include "Individual.h"
#include "Population.h"
#include "LocalSearch.h"


void PrintShortestPath(Params &params, std::vector<int> &dist, int &start, std::vector<int> &prev);
std::vector<int> DijkstraSP(std::vector< std::vector<std::pair<int, int> > > &adjList, int &start, std::vector<int> &prev);
void reduceInputGraph(Params *params);

int main(int argc, char *argv[])
{
	Commandline c(argc, argv);
	if (c.is_valid())
	{
		// Initialization of the problem data from the commandline
		Params params(c.get_path_to_instance(), c.get_path_to_solution(), c.get_seed());
		reduceInputGraph(&params);
		std::cout << "----- STARTING ALGORITHM" << std::endl;
		params.startTime = clock();
		Population pop(&params);
		LocalSearch localSearch(&params);
		pop.generateInitialPopulation();
		int maxFailedAttempts = 5000, nbFailedAttempts = 0;
		
		Individual offspring(&params);
		Individual bestSolution(&params);
		Individual::copy(&bestSolution,pop.getBestIndividual());
		printf("Best initial solution %d\n", bestSolution.getCost());
		while(nbFailedAttempts < maxFailedAttempts)
		{
			pop.crossover(&offspring);
			localSearch.run(&offspring);
			pop.placeIndividual(&offspring);
			if(offspring.getCost() < bestSolution.getCost())
			{
				Individual::copy(&bestSolution,&offspring);
				printf("Best local optima improved: %d\n", bestSolution.getCost());
				nbFailedAttempts = 0;
			}
			else 
			{
				nbFailedAttempts++;
			}
		}
		// int node = 0;
		// std::vector<int> prev;
		// std::vector<int> dist = DijkstraSP(params.adjList, node, prev);
		// // PrintShortestPath(params, dist, node, prev);

		params.endTime = clock();
		std::cout << ">BEST SOLUTION " << bestSolution.getCost() << "; TIME " << (params.endTime - params.startTime) / (double)CLOCKS_PER_SEC << "(s)" << std::endl;
		
		// Printing the solution and exporting statistics (also export results into a file)
		std::cout << "----- END OF ALGORITHM" << std::endl;
	}
	return 0;
}


void reduceInputGraph(Params *params)
{
	printf("----- START OF PREPROCESSING INSTANCE\n");
	Individual original_graph(params);
	//Copy graph
	original_graph.adjList = params->adjList;
	int nbRemovedEdges = 0;
	int nbRemovedVertices = 0;
	original_graph.removeNonTerminalLeaves();
	for(int i = 0 ; i < original_graph.adjList.size() ; i++)
	{
		if(original_graph.adjList[i].size() == 0)
		{
			nbRemovedVertices++;
			nbRemovedEdges += params->adjList[i].size();
		}
	}
	printf("nbRemovedEdges; %d; -%.2lf\n", nbRemovedEdges, nbRemovedEdges*100.0/((int)params->edgeMap.size()));
	printf("nbRemovedVertices; %d; -%.2lf\n", nbRemovedVertices,  nbRemovedVertices*100.0/((int)params->adjList.size()));
	params->adjList = original_graph.adjList;
	printf("----- END OF PREPROCESSING INSTANCE\n");
}

void PrintShortestPath(Params &params, std::vector<int> &dist, int &start, std::vector<int> &prev)
{
	std::cout << "Printing the shortest paths for node " << start << ".\n";
	
	std::vector<int> S;
	int u, target;
	u = target = 41;
	if(prev[u] > -1 || u == start){
		while( u > -1 )
		{
			S.push_back(u);
			u = prev[u];
		}
	}
	printf("source: %d, target: %d, dist[i]: %d\n",start,target,dist[target]);
	u = start;
	
	int total_weight = 0;
	for(int i = S.size() - 1; i > 0 ; i--)
	{
		total_weight += params.getEdgeWeight(S[i],S[i-1]);
		printf("%d-%d (%d) -> ", S[i], S[i-1], total_weight);
	}
	
	printf("Dist final  %d dist[.] = %d\n",total_weight,dist[target]);


	for(int i = 0; i < dist.size(); i++)
	{
		std::cout << "The distance from node " << start << " to node " << i << " is: " << dist[i] << std::endl;
	}	
}

std::vector<int> DijkstraSP(std::vector< std::vector<std::pair<int, int> > > &adjList, int &start, std::vector<int> &prev)
{
    std::cout << "Getting the shortest path from " << start << " to all other nodes.\n";
    std::vector<int> dist;
	prev.clear();
    
    // Initialize all source->vertex as infinite.
    int n = adjList.size();
    for(int i = 0; i < n; i++)
	{
        dist.push_back(1000000007); // Define "infinity" as necessary by constraints.
		prev.push_back(-1);
	}
        
    // Create a PQ.
    std::priority_queue<std::pair<int, int>, std::vector< std::pair<int, int> >, std::greater<std::pair<int, int> > > pq;
    
    // Add source to pq, where distance is 0.
    pq.push(std::make_pair(start, 0));
    dist[start] = 0;
    
    // While pq isn't empty...
    while(pq.empty() == false)
	{
        // Get min distance vertex from pq. (Call it u.)
        int u = pq.top().first;
        pq.pop();
        
        // Visit all of u's friends. For each one (called v)....
        for(int i = 0; i < adjList[u].size(); i++)
		{
            int v = adjList[u][i].first;
            int weight = adjList[u][i].second;
            
            // If the distance to v is shorter by going through u...
            if(dist[v] > dist[u] + weight)
			{
				// Update the distance of v.
				dist[v] = dist[u] + weight;
				// Insert v into the pq. 
				pq.push(std::make_pair(v, dist[v]));
				prev[v] = u;
			}
		}
	}

    
    return dist;
}
