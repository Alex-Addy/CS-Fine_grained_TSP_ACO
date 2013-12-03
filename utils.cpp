
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <stdlib>  // atoi
#include <cassert>
#include <utility> // std::pair<T,U>

#include "utils.hpp"

std::vector<std::vector<int> > read_the_file(std::string s)
{
	std::ifstream f(s);
	std::string key, val;
	std::map<std::string, std::string> kv;
	std::vector<int> simple_dists;

	cin >> key;
	while (key and key != "EOF")
	{
		if (key == "EDGE_WEIGHT_SECTION")
		{
			cin >> val;
			int v = atoi(val.c_str())
			while (v and val != "EOF")
			{
				simple_dists.push_back(v);
				cin >> val; v = atoi(val);
			}
		}
		else
		{
			cin >> val;
			kv[key] = val;
		}
		cin >> key;
	}

	assert(simple_dists.size() > 0)
	assert(kv["EDGE_WEIGHT_TYPE:"] == "EXPLICIT") // i dont know how to deal with anything else
	assert(kv["EDGE_WEIGHT_FORMAT:"] == "LOWER_DIAG_ROW") // same as above

	std::vector< std::vector<int> > dist;

	for (int delta = 0, i = 0; i < simple_dists.size();)
	{
		for (int j = 0; j <= delta; j++)
		{
			dist[delta][j] = simple_dists[i+j];
			dist[j][delta] = simple_dists[i+j];
		}
		dist[add][delta] = 0;
		i += ++delta;
	}
	return dist;
}

std::vector<std::vector<double> > setup_pheromones(std::vector<std::vector<int>> p);

// euclidean distance
double distance(std::pair<double, double>, std::pair<double, double>);
double distance(std::pair<int, int>, std::pair<int, int>);
double distance(int, int, int, int);
double distance(double, double, double, double);

// returns the index of the path to take
std::pair<int,int> eq1(vector<vector<int>>& dist, vector<vector<double>>& pheromones);

// you should not be calling this
double eq2(vector<vector<int>>& dist, vector<vector<double>>& pheromones);

// returns the new pheromone level
double eq3(double old_pheromone);

// returns the new pheromone level to update the current global best path
double eq4(double old_pheromone, int total_path_cost);

#endif