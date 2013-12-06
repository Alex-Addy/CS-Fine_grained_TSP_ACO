#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <vector>
#include <fstream>
#include <utility>

const double Q0 = 0.3;  //if > then, exploration
const double BETA = 0.5; // must be in range [0,1], a lower q favors exploration over exploitation
const double ALPHA = 0.2; // must be in range [0,1], pheremone decay factor
const double TAU = 0.3;
const int GENERATIONS = 100;  //how many times will we run this thingy
const int ANTCOUNT = 1;
//const double PHERBASE = 0.5; //base level of pheromones

// returns the dist array, it is directional
std::vector< std::vector<int> > read_the_file(std::string s);
std::vector< std::vector<double> > setup_pheromones(std::vector< std::vector<int> >& p);

// euclidean distance
double distance(std::pair<double, double>, std::pair<double, double>);
double distance(std::pair<int, int>, std::pair<int, int>);
double distance(int, int, int, int);
double distance(double, double, double, double);

/*
equation 1 and equation 2s interfaces are subject to change
*/

// returns the index of the next city to go to
std::pair<int,int> eq1(std::vector< std::vector<int> >& dist, std::vector< std::vector<double> >& pheromones);

// returns the value computed by equation 2
std::vector<double> eq2(std::vector< std::vector<int> >& dist, std::vector< std::vector<double> >& pheromones, std::vector<int>& not_visited, int cur_city);

int eq2_helper(std::vector<double>& probabilities, double rand_0_to_1);

// returns the new pheromone level
double eq3(double old_pheromone, int nextCost);

// returns the new pheromone level to update the current global best path
double eq4(double old_pheromone, int total_path_cost);

#endif
