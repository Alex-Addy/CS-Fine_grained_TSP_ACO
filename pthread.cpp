#include <vector>
#include <iostream>
#include <utility> // std::pair<T,U>
#include <pthread.h>
#include <algorithm>
#include <cmath>
#include <climits>

#include "utils.hpp"

int shortest_path_dist(std::vector< std::vector<int> > dist, std::vector< std::vector<double> > pheromones);
void* does_work(void *ptr);

//////global
int problemSize =0;
//int threadCount = 24;
std::vector<std::vector<int> > results;
std::vector<int> wholeCost;
std::vector< std::vector<int> > Distance;
std::vector<std::vector<double> > Pher;
std::vector<int> Locations;

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
	// call shortest path with itthr_count
	// then print out the answer

	std::string fileName(argv[1]);

	std::vector< std::vector<int> > dist = read_the_file(fileName);// returns a filled distance vector
	std::vector<std::vector<double> > pheromones = setup_pheromones(dist); // returns a filled pheromone vector
	
	problemSize = dist.size();
	for(int i =0; i < ANTCOUNT; i++)
	{
		std::vector<int> temp;
		results.push_back(temp);
		wholeCost.push_back(0);
	}
	
	for(int i =0; i < problemSize;i++)
		Locations.push_back(i);

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

	Pher= pheromones;
	Distance = dist;
	std::vector<pthread_t> cur;

	for(int i = 0; i < GENERATIONS; i++)
	{

		
		for(int i = 0;i < ANTCOUNT; i++)
		{
			int * ii = new int(i);
			pthread_t temp;
			pthread_create(&temp, NULL, does_work,(void*)ii);
			cur.push_back(temp);
		}
		while(!cur.empty())
		{
			pthread_join(cur.back(),NULL);
			cur.pop_back();
		}
		cur.clear();


		//global update
		//look at reuslts
		int minIndex=0,minVal = INT_MAX;
		for(int i =0; i < results.size();i++)
		{
			if(wholeCost[i] < minVal)
			{
				minIndex = i;
				minVal = wholeCost[i];
			}
		}

		//int endi = results[minIndex][results[minIndex].size()-1];
		for(int i =0; results[minIndex].size() > 1;i++)
		{
			int temp= results[minIndex].back();
			results[minIndex].pop_back();
			Pher[results[minIndex].back()][temp] = eq4(Pher[results[minIndex].back()][temp],wholeCost[minIndex]);
		}



		for(int i =0; i < cur.size();i++)
			cur[i] = 0;

	}
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

void *does_work(void *ptr)
{
	int pos = 0;
	int antDist = 0;
	int id = *((int *)ptr);
	//std::vector<double> res;
	std::vector<int> history;
	std::vector<int> unvisited = Locations;

	while(history.size() + 1 < problemSize)
	{
		//res.clear();
		//for(int i =0;i < problemSize; i++)
		//{
		//	res.push_back(0.0);
		//}

		double choice = ((double) rand() / (RAND_MAX));

		double choice2 = ((double) rand() / (RAND_MAX));

		double max = 0;
		int maxIndex =0;

		std::cout << choice<< "   "  << choice2 << std::endl;
		//std::cout << "Test" << id << std::endl;
		//std::cout << Pher[0].size() <<std::endl;
		//std::cout << choice << "   " << choice2 << "   testing Here" << std::endl;
		if(choice < Q0)
		{
			// expliait
		std::cout << "inDaIf" << std::endl;
			for(int i =0; i< problemSize; i++)
			{
				if(i == pos) continue;
				if(std::find(history.begin(), history.end(), i) != history.end()) 
					continue;

				double temp = Pher[pos][i] / pow(Distance[pos][i], BETA) ;

				if( temp > max)
				{
					max =temp;
					maxIndex = i;
				}
			}
		}
		else //we expolore
		{
std::cout << "theElse" << std::endl;

std::cout << Pher.size() << "	" << Distance.size() << "	" << unvisited.size() << "	" << pos << std::endl;
			std::vector<double> cho = eq2(Distance, Pher, unvisited, pos);

			maxIndex = eq2_helper(cho,choice2);
			max = Pher[pos][maxIndex] / pow(Distance[pos][maxIndex], BETA);
		}
std::cout << "middle	" << max << "	" << maxIndex << std::endl;
		Pher[pos][maxIndex] = eq3(Pher[pos][maxIndex],problemSize);
		antDist += Distance[pos][maxIndex];
		pos = maxIndex;
		history.push_back(maxIndex);
		int temp = *(std::find(unvisited.begin(),unvisited.end(),maxIndex));
		unvisited.erase(unvisited.begin() + temp);
	}

std::cout << "end" << std::endl;
	results[id] = history;
	wholeCost[id] = antDist;

}

