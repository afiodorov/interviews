#include "includes/queue.cpp"
#include "includes/linkedlist.cpp"
#include <iostream>

int main(int arc, char** argv) {
	int n;
	std::cout << "Enter n:" << std::endl;
	std::cin >> n;

	LinkedList<int> list;
	for(int i=0; i<20; i++) {
		list.addNode(new Node<int>(i));
	}
	std::cout << "Initial list:" << std::endl;
	std::cout << list << std::endl;

	Que<Node<int>*> queue(n);
	Node<int>* it = list.getHead();
	while(it != 0) {
		queue.push(it);
		it = it->getNext();
	}
	std::cout << queue.pop()->getData() << std::endl;
	std::cout << "Queue: " <<  queue << std::endl;
	return 0;
}
