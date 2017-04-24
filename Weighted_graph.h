/*****************************************
 * UW User ID:  rw3leung
 * Submitted for ECE 250
 * Semester of Submission:  Winter 2017
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 *  the provided code.
 *****************************************/

#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#ifndef nullptr
#define nullptr 0
#endif

#include <iostream>
#include <limits>
#include "Priority_queue.h"
#include "Exception.h"

// include whatever classes you want

class Weighted_graph {
	private:
		// your implementation here
		//  you can add both private member variables and private member functions
		int size;
		int number_of_edges;
		int *degree_array;
		double **adjacency_matrix;
		int **adjacent_nodes;
		static const double INF;
		int max( int, int) const;
		double **distances_array;
		int **states_array;
		int inserts_made_previously;
		Priority_queue **queues;

	public:
		Weighted_graph( int = 50 );
		~Weighted_graph();

		int degree( int ) const;
		int edge_count() const;
		double adjacent( int, int ) const;
		double distance( int, int );
		double distance_using_previous( int, int );

		void insert( int, int, double );

	// Friends

	friend std::ostream &operator<<( std::ostream &, Weighted_graph const & );
};

const double Weighted_graph::INF = std::numeric_limits<double>::infinity();

// Your implementation here

// Constructor
Weighted_graph::Weighted_graph( int n ):
size( max( 1, n) ),
number_of_edges( 0 ),
degree_array( new int[size] ),
adjacency_matrix( new double*[size] ),
adjacent_nodes( new int*[size] ),
inserts_made_previously( 0 ),
distances_array( new double*[size] ),
states_array( new int*[size] ),
queues( new Priority_queue*[size] ) {
	// Initializes adjacency_matrix, adjacent_nodes, and degree_array values
	for (int i = 0; i < size; ++i) {
		adjacency_matrix[i] = new double[size];
		adjacent_nodes[i] = nullptr;
		degree_array[i] = 0;
		distances_array[i] = nullptr;
		states_array[i] = nullptr;
		queues[i] = nullptr;
	}
}

// Destructor
Weighted_graph::~Weighted_graph(){

	// Clear 2D arrays and arrays of pointers
	for (int i = 0; i < size; ++i) {
		delete [] adjacency_matrix[i];
		delete [] adjacent_nodes[i];
		delete [] distances_array[i];
		delete [] states_array[i];
		delete queues[i];
	}

	delete [] degree_array;	
	delete [] adjacency_matrix;
	delete [] adjacent_nodes;
	delete [] distances_array;
	delete [] states_array;
	delete [] queues;
}

// Max method
int Weighted_graph::max( int a, int b) const {
	if (a > b) return a;
	return b;
}

// Return degree of node n
int Weighted_graph::degree( int n ) const {
	// throw illegal_argument() exception if the node n does not exist
	if (n >= size || n < 0) {
		throw illegal_argument();
	}

	return degree_array[n];
}

// Return the number of edges
int Weighted_graph::edge_count() const {
	return number_of_edges;
}

// Return the weight of the edge if nodes are adjacent and INF otherwise
double Weighted_graph::adjacent( int m, int n ) const {
	// Throw illegal_argument exception if either of the nodes do not exist
	if (m >= size || n >= size || m < 0 || n < 0) {
		throw illegal_argument();
	}

	if (m == n) return 0;
	if (adjacency_matrix[m][n] == 0) return INF;
	return adjacency_matrix[n][m];
}

// Return the weight of the shortest path between m and n
double Weighted_graph::distance(int m, int n) {
	if (inserts_made_previously == 1) inserts_made_previously = 0;
	// Throw an exception if either node is invalid
	if (m >= size || n >= size || m < 0 || n < 0) {
		throw illegal_argument();
	}
	
	// Return 0 if m = n
	if (m == n) return 0;
	
	if (distances_array[n] != nullptr && states_array[n] != nullptr && states_array[n][m] == 2) {		
			return distances_array[n][m];
	}

	if (distances_array[m] != nullptr) {
		if (states_array[m] != nullptr && states_array[m][n] == 2) {
			return distances_array[m][n];
		}

		return distance_using_previous(m, n);
	}

	double *distance;
	int *state;
	Priority_queue *PQ;
	
	// Initialize each 'vertex' for the algorithm (each vertex has state, distance from source, and parent
	// Distance array will store the weights of the paths from m to all other vertices
	distance = new double[size];
	
	// State array will store the node's state; 0 for undiscovered, 1 for discovered and in the priority queue, and 2 for out of the priority queue 
	state = new int[size];
	
	// Initialize the distance from m to itself as zero and m's state as discovered
	distance[m] = 0;
	state[m] = 1;
	
	// Initialize the priority queue
	PQ = new Priority_queue(size);
	
	// Insert the root node
	PQ->insert(0, m);

	// Loop while priority queue not empty AND state of n (target) is not 2 
	while (!PQ->empty() && state[n] != 2) {
		if (PQ->top() == n) break;
		
		int current_node = PQ->extract_min();

		state[current_node] = 2;
		
		// Loops through all the node's neighbours (from 0th adjacent node to degree-1 in adjacent_nodes array)
		for (int i = 0; i < degree_array[current_node]; ++i) {
			int neighbour = adjacent_nodes[current_node][i];
			
			// Skip checking this iteration since this neighbour is already completed
			if (state[neighbour] == 2) continue;
			
			double proposed_distance = distance[current_node] + adjacency_matrix[current_node][neighbour];
			
			// If the distance the neighbour currently holds is more than the distance achieved by pathing from current node, 
			// path from current node instead and set the current node as its parent
			if (distance[neighbour] > proposed_distance || distance[neighbour] == 0) {
				distance[neighbour] = proposed_distance;
				// Increase the state of the neighbour to discovered if it hasn't been discovered yet
				if (state[neighbour] == 0) {
					++state[neighbour];
				
					// Insert the neighbour into the PQ with updated priority (distance) 
					PQ->insert(distance[neighbour], neighbour);
				} else {
					PQ->decrease_key(distance[neighbour], neighbour);
				}
			}
		}
	}
	
	// Set the state of the searched for node to be found
	state[n] = 2;
	
	// Delete the old arrays before copying over the new one
	delete [] distances_array[m];
	delete [] states_array[m];
	delete queues[m];
	distances_array[m] = distance;
	states_array[m] = state;
	queues[m] = PQ;
	if (distances_array[m][n] == 0) return INF;
	return distances_array[m][n];
}

// Return the weight of the shortest path between m and n
double Weighted_graph::distance_using_previous(int m, int n) {
	double *distance = distances_array[m];
	int *state = states_array[m];
	Priority_queue *PQ = queues[m];
	
	// Loop while priority queue not empty AND state of n (target) is not 2 
	while (!PQ->empty() && state[n] != 2) {
		if (PQ->top() == n) break;
		int current_node = PQ->extract_min();

		state[current_node] = 2;
		
		// Loops through all the node's neighbours (from 0th adjacent node to degree-1 in adjacent_nodes array)
		for (int i = 0; i < degree_array[current_node]; ++i) {
			int neighbour = adjacent_nodes[current_node][i];
			
			// Skip checking this iteration since this neighbour is already completed
			if (state[neighbour] == 2) continue;
			
			double proposed_distance = distance[current_node] + adjacency_matrix[current_node][neighbour];
			// If the distance the neighbour currently holds is more than the distance achieved by pathing from current node, 
			// path from current node instead and set the current node as its parent
			if (distance[neighbour] > proposed_distance || distance[neighbour] == 0) {
				distance[neighbour] = proposed_distance;
				// Increase the state of the neighbour to discovered if it hasn't been discovered yet
				if (state[neighbour] == 0) {
					++state[neighbour];
				
					// Insert the neighbour into the PQ with updated priority (distance) 
					PQ->insert(distance[neighbour], neighbour);
				} else {
					PQ->decrease_key(distance[neighbour], neighbour);
				}
			}
		}
	}
	
	// Set the state of the searched for node to be found
	state[n] = 2;
	if (distances_array[m][n] == 0) return INF;
	return distances_array[m][n];
}

// Insert edge between m and n with weight of w
void Weighted_graph::insert( int m, int n, double w) {
	// Throw an exception if w <= 0, m or n are not nodes, or if m = n
	if (w <= 0 || m >= size || m < 0 || n < 0 || n >= size || m == n) {
		throw illegal_argument();
	}
	
	// Set inserts made flag to true
	if (inserts_made_previously == 0) {
		for (int i = 0; i < size; ++i) {
			delete [] distances_array[i];
			distances_array[i] = nullptr;
			delete [] states_array[i];
			states_array[i] = nullptr;
		}
	}

	// If this is a new edge, update the adjacent_nodes array for both m and n and increase their degrees by 1 and the number of edges by 1
	if (adjacency_matrix[m][n] == 0 && adjacency_matrix[n][m] == 0) {
		// If the degree of m is zero (no adjacent_nodes set created) create the adjacent_nodes array for m
		if (degree(m) == 0) adjacent_nodes[m] = new int[size];

		// If the degree of n is zero (no adjacent_nodes set created) create the adjacent_nodes array for n
		if (degree(n) == 0) adjacent_nodes[n] = new int[size];
	
		// Update the adjacent_nodes arrays for m and n to include each other
		adjacent_nodes[m][degree(m)] = n;
		adjacent_nodes[n][degree(n)] = m;
		
		// Increase the degrees of both m and n
		++degree_array[m];
		++degree_array[n];
		
		// Increment the counter for the number of edges
		++number_of_edges;
	}

	// Update the adjacency_matrix with the new weight
	adjacency_matrix[m][n] = w;
	adjacency_matrix[n][m] = w;
	inserts_made_previously = 1;
}

// You can modify this function however you want:  it will not be tested

std::ostream &operator<<( std::ostream &out, Weighted_graph const &graph ) {
	return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif

