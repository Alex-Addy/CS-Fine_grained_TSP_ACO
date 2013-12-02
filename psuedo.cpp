#include <vector>
#include <iostream>

// euclidean distance
double distance(std::pair<double, double>, std::pair<double, double>);
double distance(std::pair<int, int>, std::pair<int, int>);

int shortest_path_dist(vector< vector<int> >);

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		std::cerr << "I needs a file dammit! << std::endl;
		return 1;
	}
	std::fstream f(argv[1]);
	
	// well what now?
	// something about an algorithm...
	// oh yes! i think i need to build the distance array
	// call shortest path with it
	// then print out the answer
	std::cout << answer << std::endl;
}

int shortest_path_dist(std::vector< std::vector<int> > dist)
{
	// for each iteration
		// for each ant : IN PARALLEL
			// start a new thread,initialize the ant
			// share distance and pheromone graph for the thread
			// while a tour is not finished
				// choose the next city (eq 1,2)
				// atomic: local pheromone update (eq 3)
			// end while // end of ant's travel
			// atomic: global pheromone update (eq 4)
			// terminate the thread, release resources
		// end for
	// end for // end of iteration
}
