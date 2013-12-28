#include <iostream>
#include "includes/queueFromStack.cpp"

int main(int, char**) {
	Queue<int> que;
	for(int i=0; i<20; i++) {
		que.enqueue(std::unique_ptr<int>(new int(i)));
	}

	for(int i=0; i<10; i++) {
		std::cout << *que.dequeue() << " ";
	}

	for(int i=20; i<30; i++) {
		que.enqueue(std::unique_ptr<int>(new int(i)));
	}

	for(int i=0; i<20; i++) {
		std::cout << *que.dequeue() << " ";
	}

	return 0;
}
