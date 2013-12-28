#include <iostream>
#include "includes/stackSmart.cpp"
#include <random>
#include <cstdlib>
#include <memory>

template<typename T>
void stackSort(int n, Stack<T>& source, Stack<T>& dest, bool isMax=true) {
	if(n > 0) {
		if(isMax) leaveMinInSource(n, source, dest);
		else leaveMaxInSource(n, source, dest);
		stackSort(n-1, dest, source, !isMax);
	} else {
		Stack<T> *mySource(nullptr), *myDest(nullptr);
		if(!isMax) {
			mySource = &dest;
			myDest = &source;
		} else {
			mySource = &source;
			myDest = &dest;
		}
		while(!mySource->isEmpty()) {
			myDest->push(std::unique_ptr<T>(std::move(mySource->popPtr())));
		}
	}
};

template<typename T>
void leaveMinInSource(int n, Stack<T>& source, Stack<T>& dest) {
	T min = source.pop();
	int counter=0;
	while(counter < n-1) {
		counter++;
		T b = source.pop();
		T max;
		if(min>b) {
			max = min;
			min = b;
		} else {
			max = b;
		}
		dest.push(std::unique_ptr<T>(new T(max)));
	}
	source.push(std::unique_ptr<T>(new T(min)));

}

template<typename T>
void leaveMaxInSource(int n, Stack<T>& source, Stack<T>& dest) {
	T max = source.pop();
	int counter=0;
	while(counter < n-1) {
		counter++;
		T b = source.pop();
		T min;
		if(max<b) {
			min = max;
			max = b;
		} else {
			min = b;
		}
		dest.push(std::unique_ptr<T>(new T(min)));
	}
	source.push(std::unique_ptr<T>(new T(max)));

}

int main(int, char**) {
	srand(time(NULL));
	const int SIZE = 20;
	Stack<double> s, sorted;
	for(int i=0; i<SIZE; i++) {
		s.push(std::unique_ptr<double>(
		new double(rand() / double(RAND_MAX))));
	}
	stackSort(SIZE, s, sorted);
	std::cout << sorted << std::endl;
	return 0;
}
