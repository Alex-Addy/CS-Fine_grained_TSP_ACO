### Fine-grained Parallel Ant Colony Optimization for the Traveling Salesman Problem
#### Authors: Alexander Addy, Brad Santoro, Walter Wolfe

### Abstract

####The Traveling Salesman Problem(TSP) is the question: 

Given a list of cities and the distances between each pair of cities, what is the shortest path that visits each city exactly once and returns to the orgin city? This problem is NP-hard, appearing in many areas, “such as planning, logistics, and the manufacture of microchips”. Formally, TSP can be represented as an “an undirected weighted graph, such that cities are the graph's vertices, paths are the graph's edges, and a path's distance is the edge's length”.

As a way of getting around the inherent intractibility of the problem, there are many heuristic algorithms for it.
These algorithms use heuristics in order to give a solution that is within a reasonable amount of the actual solution.
This relaxation of correctness allows for a possible solution to be found in a much quicker time. Some heuristics also allow for easier parallelization of the algorithm.

####The Ant Colony Optimization(ACO):
The application of techniques learned through the observance of ants to path finding. ACO in application to TSP is a probabilistic heuristic technique.  Ants travel along paths in a pseudo-random manner, attempting to visit every city exactly once. The chance of an ant traveling down a particular path is determined by the amount of “pheromone” on the path and the distance of the path[1]. When an ant completes a tour of the cities, the ant lays down pheromone on each path in its tour, with the amount being inversely proportional to the length of the tour. The way in which this approaches the optimal solution is through having the pheromone evaporate, by doing so longer paths will have less pheromone on them than the shorter paths, and eventually the only path traveled will be a solution that is close to the optimal.

####Implementation:
The original plan was to have an implementation in both Pthreads and OpenMP. However due to time contraints we were unable to complete both. As such we only have a pthreads implementation to go off of.

The reference used for this implementation is reference [0]. We followed the core of the algorithm psuedocode as well as using the four equations described in the paper.


####Test Cases:
for the test cases we found a repository of travling salesman problem datasets and the solutions to them at [1], we used the 'gr' cases from the symmetric TSP data set.

####Results:

#####Environment:
These test cases were run on the linux side of the lab machines.
The constants talked about in the paper have been set to: q<sub>0</sub> = 0.0245, &beta; = 0.765, &alpha; = 0.45, &tau; = 0.3. These were arrived at after various amounts of tweaking for the data sets, in an attempt to get closer to the correct value.

For the data sets the number in the name refers to the number of cities in it. Also each graph is completely connected, so the number of connections is n<sup>2</sup>.

For the following tests: there were 500 iterations, with the best path among all of them reported; and there were 24 'ants' or threads running.

#####Run results:
Time format (secs, &mu;secs), then best path found for each test file.
<table>
<tr><th>gr17.tsp</th><th></th><th>gr24.tsp</th><th></th><th>gr48.tsp</th><th></th></tr>
<tr><td>0, 279845</td><td>2187</td><td>1, 680745</td><td>1370</td><td>0, 581317</td><td>5624</td></tr>
<tr><td>0, 273655</td><td>2187</td><td>0, 310284</td><td>1397</td><td>1, 413084</td><td>5762</td></tr>
<tr><td>1, 719743</td><td>2168</td><td>0, 305045</td><td>1371</td><td>1, 409592</td><td>5520</td></tr>
<tr><td>0, 279556</td><td>2187</td><td>1, 692226</td><td>1396</td><td>0, 599382</td><td>5691</td></tr>
<tr><td>0, 279228</td><td>2187</td><td>0, 308061</td><td>1336</td><td>1, 408210</td><td>5791</td></tr>
<tr><td>1, 723068</td><td>2158</td><td>0, 316047</td><td>1396</td><td>0, 598798</td><td>5776</td></tr>
<tr><td>0, 281014</td><td>2158</td><td>1, 688951</td><td>1349</td><td>1, 399834</td><td>5607</td></tr>
<tr><td>0, 273162</td><td>2170</td><td>0, 307504</td><td>1409</td><td>1, 414131</td><td>5633</td></tr>
<tr><td>0, 275780</td><td>2158</td><td>0, 311736</td><td>1384</td><td>0, 599203</td><td>5507</td></tr>
<tr><td>1, 722428</td><td>2168</td><td>1, 685006</td><td>1391</td><td>1, 399293</td><td>5536</td></tr>
<tr><td>0, 273157</td><td>2187</td><td>0, 307663</td><td>1429</td><td>0, 603898</td><td>5722</td></tr>
<tr><td>0, 272537</td><td>2187</td><td>0, 310614</td><td>1409</td><td>1, 404581</td><td>5733</td></tr>
<tr><td>0, 277003</td><td>2187</td><td>1, 688935</td><td>1445</td><td>1, 397279</td><td>5701</td></tr>
<tr><td>1, 725904</td><td>2187</td><td>0, 315996</td><td>1378</td><td>0, 603132</td><td>5696</td></tr>
<tr><td>0, 276688</td><td>2187</td><td>0, 305665</td><td>1354</td><td>1, 405900</td><td>5457</td></tr>
<tr><td>0, 274314</td><td>2158</td><td>1, 691869</td><td>1362</td><td>0, 593631</td><td>5581</td></tr>
<tr><td>1, 722981</td><td>2168</td><td>0, 367978</td><td>1398</td><td>1, 407229</td><td>5511</td></tr>
<tr><td>0, 277332</td><td>2158</td><td>0, 311912</td><td>1366</td><td>1, 400878</td><td>5640</td></tr>
<tr><td>0, 277964</td><td>2168</td><td>1, 694110</td><td>1378</td><td>0, 586828</td><td>5309</td></tr>
<tr><td>0, 279599</td><td>2158</td><td>0, 317370</td><td>1374</td><td>1, 406923</td><td>5632</td></tr>
</table>

Average error was calculated by finding the difference between each calculated best path and the actual best path, then dividing by the number of measurements.

<table>
<tr><th>Problem</th><th>Mean run time (&mu;secs)</th><th>Mean best path</th><th>Actual best path</th><th>Avg Err</th></tr>
<tr><td>gr17</td><td>638247.9  </td><td>2173.65</td><td>2085</td><td>88.65 </td></tr>
<tr><td>gr24</td><td>795885.85 </td><td>1384.6 </td><td>1272</td><td>112.6 </td></tr>
<tr><td>gr48</td><td>1081656.15</td><td>5621.45</td><td>5046</td><td>575.45</td></tr>
</table>

####Conclusions:

###References:
[0] Ali Hadian, Saeed Shahrivari and Behrouz Minaei-bidgoli. Article: Fine-grained Parallel Ant Colony System for Shared-Memory Architectures. International Journal of Computer Applications 53(8):8-13, September 2012. Published by Foundation of Computer Science, New York, USA.

[1] http://comopt.ifi.uni-heidelberg.de/software/TSPLIB95/
