# Weighted Graph Project (Dijkstra Implementation)
This is an implementation for a weighted graph containing only positive weights and using Dijkstra's algorithm for finding minimum paths. 
This solution was made for ECE 250 - Algorithms and Data Structures and had the fastest tested runtime out of 149 student submissions.

## Features
The weighted graph class allows for creation of an undirected and positively weighted graph.
The class' constructor is called with a single argument, an integer for the number of nodes in the graph, and creates a graph with nodes numbered from 0 to size - 1.
The class supports function calls to insert new edges, retrieve the degree of a specific node, retrieve the number of edges in the graph, retrieve the weight of the edge between any two nodes, and to find the shortest distance between any two nodes on the graph.

The priority queue class uses a min heap to operate and supports inserts, extractions of the minimum value, and decreasing the key of a given value in the queue. 

## Dijkstra's Implementation
Given node m, the distance method returns the weight of the shortest path to node n.
The distance method utilizes Dijkstra's algorithm for finding the shortest path and uses my priority queue class to progress the algorithm using the distances of the nodes as keys.

Starting from node m, the method 'discovers' each adjacent node and adds them to the prioirty queue after assigning them a distance based on the weight of each edge. The algorithm then begins extending the algorithm's reach by extracting the minimum value from the priority queue and continuing to repeat the process on the extracted node. This algorithm continues until either the extracted node is node n or until the priority queue is empty, implying that there is no path from node m to node n.

### Optimizations
Perhaps the most crucial runtime optimization is saving the priority queue and states of all nodes for each distance method call starting at any node. By doing so, if any node's distance had been calculated as an intermediate distance, it would be easily accesible and the algorithm would have a constant runtime. Furthermore, saving the priority queue also removes the need to recalculate intermediate distances if the requested destination node's distance had not yet been calculated as the algorithm progresses in the same manner every time it is run so long as no values in the graph have been changed.

## Screenshots of Official Results
![Screenshot](/Project_Benchmark_Results/dijkstrasranking.PNG?raw=true "Email of Results")
![Screenshot](/Project_Benchmark_Results/dijkstraslearnproof.PNG?raw=true "Project Results Announcement")

