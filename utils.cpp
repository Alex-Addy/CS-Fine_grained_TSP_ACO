
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <stdlib.h>  // atoi
#include <cassert>
#include <utility> // std::pair<T,U>
#include <cmath>   // sqrt
#include <algorithm>

#include "utils.hpp"

using namespace std;

std::vector< std::vector<int> > read_the_file(std::string s)
{
	ifstream f(s.c_str());
	string key, val;
	map<std::string, std::string> kv;
	vector<int> simple_dists;

	getline(f, key, ' ');
	while (key != "" && key != "EOF")
	{
		if (key == "EDGE_WEIGHT_SECTION")
		{
			getline(f, val);
			int v = atoi(val.c_str());
			while (v && val != "EOF")
			{
				simple_dists.push_back(v);
				getline(f, val);
				v = atoi(val.c_str());
			}
		}
		else
		{
			getline(f, val);
			kv[key] = val;
		}
		getline(f, key);
	}

	assert(simple_dists.size() > 0);
	assert(kv["EDGE_WEIGHT_TYPE:"] == "EXPLICIT"); // i dont know how to deal with anything else
	assert(kv["EDGE_WEIGHT_FORMAT:"] == "LOWER_DIAG_ROW"); // same as above

	std::vector< std::vector<int> > dist;

	for (int delta = 0, i = 0; i < simple_dists.size(); )
	{
		for (int j = 0; j <= delta; j++)
		{
			dist[delta][j] = simple_dists[i+j];
			dist[j][delta] = simple_dists[i+j];
		}
		dist[i][delta] = 0;
		i += ++delta;
	}
	return dist;
}

std::vector< std::vector<double> > setup_pheromones(std::vector< std::vector<int> >& dists)
{
	double tau_0 = 1.0 / (dists.size() * TAU);

	std::vector< std::vector<double> >(dists.size(), std::vector<double>(dists.size(), tau_0));
}

// euclidean distance
// this is really unnecessary, but i dont feel like bothering with templates
double distance(std::pair<double, double> p1, std::pair<double, double> p2)
{
	return distance(p1.first, p1.second, p2.first, p2.second);
}
double distance(std::pair<int, int> p1, std::pair<int, int> p2)
{
	return distance(p1.first, p1.second, p2.first, p2.second);
}
double distance(int x1, int y1, int x2, int y2)
{
	int xd = x1-x2, yd = y1-y2;
	return sqrt(xd*xd + yd*yd);
}
double distance(double x1, double y1, double x2, double y2)
{
	double xd = x1-x2, yd = y1-y2;
	return sqrt(xd*xd + yd*yd);
}

// returns the index of the path to take
std::pair<int,int> eq1(vector<vector<int> >& dist, vector<vector<double> >& pheromones)
{
  pair<int,int> x(0,0);
  
  
  return x;
}

// you should be calling this
double eq2(vector<vector<int> >& dist, vector<vector<double> >& pheromones)
{
  return 0;
}

// returns the new pheromone level
double eq3(double old_pheromone, int num_cities)
{
  //check the nearest cost thing, might not need and just use a constant
  return (1-ALPHA) * old_pheromone + ALPHA / (num_cities * TAU);
}

// returns the new pheromone level to update the current global best path
double eq4(double old_pheromone, int total_path_cost)
{
  return (1- ALPHA) * old_pheromone + ALPHA / total_path_cost;
}