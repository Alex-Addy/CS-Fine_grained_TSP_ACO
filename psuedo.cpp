
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
	// i think i need to build the distance array
}
