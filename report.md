### Fine-grained Parallel Ant Colony Optimization for the Traveling Salesman Problem
#### Authors: Alexander Addy, Brad Santoro, Walter Wolfe

### Abstract

The Traveling Salesman Problem(TSP) is the question: 
Given a list of cities and the distances between each pair of cities, what is the shortest path that visits each city exactly once and returns to the orgin city?
This problem is NP-hard.

As a way of getting around the inherent intractibility of the problem, there are many heuristic algorithms for it.
These algorithms use heuristics in order to give a solution that is within a reasonable amount of the actual solution.
This relaxation of correctness allows for a possible solution to be found in a much quicker time.

The Ant Colony Optimization(ACO) is a probabilistic technique for finding a good path through a graph. It lends itself to TSP very well.

In this project we have implemented a fine-grained version of ACO for TSP.
There are two implementations: pthreads and openmp.
