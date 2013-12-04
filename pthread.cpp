#include <vector>
#include <iostream>
#include <utility> // std::pair<T,U>

#include "utils.hpp"

int shortest_path_dist(std::vector< std::vector<int> > dist, std::vector< std::vector<double> > pheromones);

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		std::cerr << "I needs a file dammit!" << std::endl;
		return 1;
	}
	// well what now?
	// something about an algorithm...
	// oh yes! i think i need to build the distance and pheromones array
	// call shortest path with it
	// then print out the answer
	
	std::string fileName(argv[1]);
	
	std::vector< std::vector<int> > dist = read_the_file(fileName);// returns a filled distance vector
	std::vector<std::vector<double> > pheromones = setup_pheromones(dist); // returns a filled pheromone vector

	// start time
	int answer = shortest_path_dist(dist, pheromones);
	// end time

	std::cout << answer << std::endl;
}

// this algorithm has a structure similar to floyds
// so look there for inspiration
// note: a thread pool is the sort of thing desired
int shortest_path_dist(std::vector< std::vector<int> > dist, std::vector< std::vector<double> > pheromones)
{
	// start all needed threads
	// for each iteration
		// for each ant : IN PARALLEL
			// initialize the ant
			// share distance and pheromone graph for the thread
			// while a tour is not finished
				// choose the next city (eq 1,2)
				// atomic: local pheromone update (eq 3) // after reading the paper (pg 3-4), it may be possible to drop this with minimal adverse affect, we will have to time with and without
			// end while // end of ant's travel
			// atomic: global pheromone update (eq 4)
			// terminate the thread, release resources
		//}
		// barrier: all ants
	//} // end of iteration
}

