# Weighted Graph Project (Dijkstra Implementation)
This is an implementation for a weighted graph containing only positive weights and using Dijkstra's algorithm for finding minimum paths. 
This solution was made for ECE 250 - Algorithms and Data Structures and had the fastest tested runtime out of 149 student submissions.

## Features
The weighted graph class allows for creation of an undirected and positively weighted graph.
The class' constructor is called with a single argument, an integer for the number of nodes in the graph, and creates a graph with nodes numbered from 0 to size - 1.
The class supports function calls to insert new edges, retrieve the degree of a specific node, retrieve the number of edges in the graph, retrieve the weight of the edge between any two nodes, and to find the shortest distance between any two nodes on the graph.

## Dijkstra's Implementation
The distance method utilizes Dijkstra's method of finding the shortest path and uses my priority queue class to progress the algorithm. 

## Screenshots of Official Results
![Screenshot](/Project_Benchmark_Results/dijkstrasranking.PNG?raw=true "Email of Results")
![Screenshot](/Project_Benchmark_Results/dijkstraslearnproof.PNG?raw=true "Project Results Announcement")

