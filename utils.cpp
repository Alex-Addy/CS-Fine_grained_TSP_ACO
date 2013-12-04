
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <stdlib>  // atoi
#include <cassert>
#include <utility> // std::pair<T,U>
#include <cmath>   // sqrt
#include <ctime>

#include "utils.hpp"

using namespace std;

std::vector<std::vector<int> > read_the_file(std::string s)
{
	std::ifstream f(s);
	std::string key, val;
	std::map<std::string, std::string> kv;
	std::vector<int> simple_dists;

	f >> key;
	while (key and key != "EOF")
	{
		if (key == "EDGE_WEIGHT_SECTION")
		{
			f >> val;
			int v = atoi(val.c_str())
			while (v and val != "EOF")
			{
				simple_dists.push_back(v);
				f >> val; v = atoi(val);
			}
		}
		else
		{
			f >> val;
			kv[key] = val;
		}
		f >> key;
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

std::vector< std::vector<double> > setup_pheromones(std::vector< std::vector<int> > p);

// euclidean distance
// this is really unnecessary, but i dont feel like bothering with templates
double distance(std::pair<double, double>, std::pair<double, double>)
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

  return 0;
}

// you should be calling this
double eq2(vector<vector<int> >& dist, vector<vector<double> >& pheromones)
{
 
  return 0;
}

// returns the new pheromone level
double eq3(double old_pheromone)
{
 
  return 0;
}

// returns the new pheromone level to update the current global best path
double eq4(double old_pheromone, int total_path_cost)
{
  
}