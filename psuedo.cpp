#include <vector>
#include <iostream>
#include <utility> // std::pair<T,U>

#include "utils.hpp"

using namespace std;

int shortest_path_dist(vector< vector<int> >, vector< vector<double> > v);

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

	std::vector< std::vector<int> > dist = read_the_file(string(argv[1])); // returns a filled distance vector
	std::vector< std::vector<double> > pheromones = setup_pheromones(dist); // returns a filled pheromone vector

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

/* for updating there are a few possibilities

	1. do not do a local update:
		instead, once done with a tour, do an update for all the paths used for the tour using the global update equation
			where the cost of the 'best path' is the total cost of the tour.
		this ends up being somehthing like a reduce, as everyone wants to update n paths,
			and near the end most of the updates will be happening to the same paths
	2. do the local update and the global update described by the above
	3. do the local update, and then only the master thread will do the global update to the global best path
		this is a problem because now we have to find the best path, which if we knew what it was we would be done
	4. do the local update
		have all the ant's solutions compared and only the one with the best will update the path

	1 or 4 are probably the best options
*/