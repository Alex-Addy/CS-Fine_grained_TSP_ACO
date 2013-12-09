#include <vector>
#include <iostream>
#include <utility> // std::pair<T,U>
#include <pthread.h>
#include <algorithm>
#include <cmath>
#include <climits>
#include <time.h>

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
std::vector<std::vector<double> > Randoms;

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

	for(int i =1; i < dist.size(); i++)
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
	std::vector<int> best;
	srand(time(NULL));
	for(int i = 0; i < GENERATIONS; i++)
	{
		for(int i =0; i < ANTCOUNT; i++)
		{
		  std::vector<double> temp;
		  Randoms.push_back(temp);
		  for(int j=0; j < (problemSize * 2) +1; j++)
		    Randoms[i].push_back((double) rand() / (RAND_MAX));
		}
		    

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

		for(int i =0; results[minIndex].size() > 1;i++)
		{
			int temp= results[minIndex].back();
			results[minIndex].pop_back();
			Pher[results[minIndex].back()][temp] = eq4(Pher[results[minIndex].back()][temp],wholeCost[minIndex]);
			//std::cout << "best val: " << minVal << std::endl;
			best.push_back(minVal);
		}

		cur.clear();
		std::cout << "Best of gen " << i << " is: " << minVal < std::endl;
	}

	int mini = INT_MAX;
	int miniIndex =0;

	for(int i=0; i< best.size();i++)
	{
		if(best[i] < mini)
		{
			miniIndex =i;
			mini = best[i];
		}
	}

	return mini;
}

void *does_work(void *ptr)
{
	int pos = 0;
	int antDist = 0;
	int id = *((int *)ptr);
	std::vector<int> history;
	std::vector<int> unvisited = Locations;
	bool flag = false;
	int r=0; //what random we are on;
	while(!unvisited.empty())
	{
		std::cout << pos << std::endl;

		double choice = Randoms[id][r++];

		double choice2 = Randoms[id][r++];

		double max = 0.0;
		int maxIndex =0;

		//std::cout << choice<< "   "  << choice2 << std::endl;
		if(choice > Q0)
		{
			// expliait
			//std::cout << "We X-polit" << std::endl;
			for(int i =0; i< unvisited.size(); i++)
			{
				double temp = Pher[pos][ unvisited[i] ] / pow(Distance[pos][ unvisited[i] ], BETA);
				//std::cout << "part is: " << temp << std::endl;
				if( temp > max)
				{
					max =temp;
					maxIndex = unvisited[i];
				}
			}
		}
		else //we expolore
		{
			//std::cout << "We Explore" << std::endl;

			std::vector<double> cho = eq2(Distance, Pher, unvisited, pos);

			maxIndex = eq2_helper(cho,choice2);
			max = Pher[pos][maxIndex] / pow(Distance[pos][maxIndex], BETA);
		}
		//std::cout << "Selection, Val/Pos:" << max << "	" << maxIndex << std::endl;
		Pher[pos][maxIndex] = eq3(Pher[pos][maxIndex],problemSize);
		antDist += Distance[pos][maxIndex];
		pos = maxIndex;
		history.push_back(maxIndex);
		int temp = std::find(unvisited.begin(),unvisited.end(),maxIndex) - unvisited.begin();
		//for(int i =0; i < unvisited.size();i++)
		//	std::cout << unvisited[i] << " ";
		//std::cout << std::endl;
		//std::cout << "Find: " << temp << "/" << unvisited.size() << std::endl;
		unvisited.erase(unvisited.begin() + temp);
		//std::cout << "Ant Current distance" << antDist << std::endl;
		if(unvisited.empty() && !flag)
		{
			flag = true;
			unvisited.push_back(0);
		}
	}

	std::cout << "End Value: " << antDist << std::endl;
	results[id] = history;
	wholeCost[id] = antDist;

}

