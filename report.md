### Fine-grained Parallel Ant Colony Optimization for the Traveling Salesman Problem
#### Authors: Alexander Addy, Brad Santoro, Walter Wolfe

### Abstract

####The Traveling Salesman Problem(TSP) is the question: 

Given a list of cities and the distances between each pair of cities, what is the shortest path that visits each city exactly once and returns to the orgin city? This problem is NP-hard, appearing in many areas, “such as planning, logistics, and the manufacture of microchips”. Formally, TSP can be represented as an “an undirected weighted graph, such that cities are the graph's vertices, paths are the graph's edges, and a path's distance is the edge's length”.

As a way of getting around the inherent intractibility of the problem, there are many heuristic algorithms for it.
These algorithms use heuristics in order to give a solution that is within a reasonable amount of the actual solution.
This relaxation of correctness allows for a possible solution to be found in a much quicker time.

####The Ant Colony Optimization(ACO):
is the application of techniques learned through the observance of ants to path finding. ACO in application to TSP is a probabilistic heuristic technique.  Ants travel along paths in a pseudo-random manner, attempting to visit every city exactly once. The chance of an ant traveling down a particular path is determined by the amount of “pheromone” on the path and the distance of the path[1]. When an ant completes a tour of the cities, the ant lays down pheromone on each path in its tour, with the amount being inversely proportional to the length of the tour. The way in which this approaches the optimal solution is through having the pheromone evaporate, by doing so longer paths will have less pheromone on them than the shorter paths, and eventually the only path traveled will be a solution that is very close to the optimal.

In this project we have implemented a fine-grained version of ACO for TSP.
There are two implementations: pthreads and openmp.

