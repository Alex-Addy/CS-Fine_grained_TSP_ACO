#include <vector>
#include <iostream>
#include <fstream>
#include <random> // correct?

const int Q0 = 0.5 // must be in range [0,1], a lower q favors exploration over exploitation
const int ALPHA = 0.5 // must be in range [0,1], pheremone decay factor

// euclidean distance
double distance(std::pair<double, double>, std::pair<double, double>);
double distance(std::pair<int, int>, std::pair<int, int>);
double distance(int, int, int, int);
double distance(double, double, double, double);

int shortest_path_dist(vector< vector<int> >);

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		std::cerr << "I needs a file dammit!" << std::endl;
		return 1;
	}
	std::ifstream f(argv[1]);
	
	// well what now?
	// something about an algorithm...
	// oh yes! i think i need to build the distance and pheromones array
	// call shortest path with it
	// then print out the answer

	// start time
	int answer = shortest_path_dist(dist, pheromones)
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
		}
		// barrier: all ants
	} // end of iteration
}
