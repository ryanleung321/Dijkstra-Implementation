#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

// Data structure for key (distance) and value (node) pairs
class pair {
	public:
		double priority;
		int node;
		pair(double, int);
		pair();
		~pair();
};

class Priority_queue {
	private:
		int capacity;
		int heap_size;
		pair *heap;
		int *node_map;

	public:
		Priority_queue( int = 10 );
		Priority_queue();
		~Priority_queue();
		bool empty() const;
		int left( int & ) const;
		int right(int & ) const;
		int parent(int & ) const;
		void heapify( int );
		void insert( double, int );
		int extract_min();
		void swap( int &, int & ) const;
		void decrease_key( double, int );
		int top() const;
};

pair::pair( double n, int m):
priority(n),
node(m) {
	// empty constructor
}

pair::pair(){}
	
pair::~pair(){
	// empty destructor
}


Priority_queue::Priority_queue( int n ):
heap_size( 0 ),
capacity( n <= 0 ? 1 : n ),
heap( new pair[capacity] ),
node_map( new int[capacity] ) {
	
	// Initialize all values of node_map to -1 (not in the queue)
	for (int i = 0; i < capacity; ++i) {
		node_map[i] = -1;
	}
}

Priority_queue::Priority_queue() {}

Priority_queue::~Priority_queue() {
	// Delete the arrays
	delete [] heap;
	delete [] node_map;
}

// Returns true if empty
bool Priority_queue::empty() const {
	return (heap_size == 0);
}

// Swaps two pairs and updates the positions of each node in the queue
void Priority_queue::swap( int &m, int &n ) const {
	// n is the position of heap[n].node in the heap, m is the position of heap[m].node in the heap
	int temp_int = n;
	node_map[heap[n].node] = m;
	node_map[heap[m].node] = temp_int;
	pair temp_pair = heap[n];
	heap[n] = heap[m];
	heap[m] = temp_pair;
}

int Priority_queue::left( int &n ) const {
	return 2 * n + 1;
}

int Priority_queue::right( int &n ) const {
	return 2 * n + 2;
}

int Priority_queue::parent( int &n ) const {
	return ((n + 1) / 2) - 1;
}

// Heapify function that swaps n with its smallest child based on priority then calls again on new position
void Priority_queue::heapify( int n ) {
	int smallest = n;
	int left_child = left(n);
	int right_child = right(n);
	
	// Set smallest to be whichever value has the smallest priority
	if (left_child < heap_size && heap[left_child].priority < heap[n].priority) {
		smallest = left_child;
	}

	if (right_child < heap_size && heap[right_child].priority < heap[smallest].priority) {
		smallest = right_child;
	}
	
	// If a smaller value than intial was found, swap the two and call again on new position of n
	if (smallest != n) {
		swap(smallest, n);
		heapify(smallest);
	}
}

// Insert new node into the heap
void Priority_queue::insert( double key, int node ) {
	// Create new pair to be inserted
	pair new_pair(key, node);
	
	// Insert new pair at back of heap
	heap[heap_size] = new_pair;
	
	int i = heap_size;
	
	// Increase the heap size
	++heap_size;
	
	// While the parent is larger than the new value, move the parent value into the child and recheck the inserted value against next parent
	while (i > 0 && key < heap[parent(i)].priority) {
		heap[i] = heap[parent(i)];
		
		// Update the pair that was moved down with the lower position in node_map
		node_map[heap[i].node] = i;
		i = parent(i);
	}
	
	// Insert new_pair into its final location
	heap[i] = new_pair;
	
	// Store the location of this node into the node_map
	node_map[node] = i;
}

// Return the node value at the front of the queue
int Priority_queue::extract_min() {
	int minimum = heap[0].node;
	node_map[minimum] = -1;
	heap[0] = heap[--heap_size];
	heapify(0);
	return minimum;
}

void Priority_queue::decrease_key( double new_priority, int node ) {
	int position = node_map[node];
	if (position == -1) {
		insert(new_priority, node);
	} else {
		// Update the priority of the node
		heap[position].priority = new_priority;
		
		// Store the updated pair
		pair updated_pair = heap[position];

		// Move parent down as long as child priority is smaller
		while (position > 0 && new_priority < heap[parent(position)].priority) {
			heap[position] = heap[parent(position)];
			
			node_map[heap[position].node] = position;
			position = parent(position);
		}
		
		// Restore the updated pair into its new position and update the node map
		heap[position] = updated_pair;
		node_map[node] = position;
	}
}

int Priority_queue::top() const {
	return heap[0].node;
}

#endif

