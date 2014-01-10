#include <iostream>
#include <sstream>
#include "includes/heap.cpp"

using heap::MaxHeap;

int main(int, char**) {
	srand(time(NULL));
	const int SIZE = 20;
	std::vector<double> vector;
	for(int i=0; i<SIZE; i++) {
		vector.push_back(rand() / double(RAND_MAX));
	}
	MaxHeap<double> heap(vector);
	heap.sort();
	std::cout << heap;

	return 0;
}
