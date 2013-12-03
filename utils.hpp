
#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <vector>
#include <fstream>
#include <utility>

const int Q0 = 0.5 // must be in range [0,1], a lower q favors exploration over exploitation
const int ALPHA = 0.5 // must be in range [0,1], pheremone decay factor

// returns the dist array, it is directional
std::vector< std::vector<int> > read_the_file(std::string s);
std::vector< std::vector<double> > setup_pheromones(std::vector< std::vector<int> > p);

// euclidean distance
double distance(std::pair<double, double>, std::pair<double, double>);
double distance(std::pair<int, int>, std::pair<int, int>);
double distance(int, int, int, int);
double distance(double, double, double, double);

// returns the index of the path to take, will call eq2 if needed
std::pair<int,int> eq1(vector< vector<int> >& dist, vector< vector<double> >& pheromones);

// returns the new pheromone level
double eq3(double old_pheromone);

// returns the new pheromone level to update the current global best path
double eq4(double old_pheromone, int total_path_cost);

#endif