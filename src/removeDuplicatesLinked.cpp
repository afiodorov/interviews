#include "includes/linkedlist.cpp"
#include <iostream>

template<class T>
void removeNodeAfter(Node<T>* n) {
	if(n == 0) return;
	Node<T>* beRemoved = n->getNext();
	n->setNext((beRemoved == 0) ? 0 : beRemoved->getNext());
	delete beRemoved;
}

template<class T>
void removeDuplicates(LinkedList<T>& list) {
	if(list.getHead() == 0) return;
	Node<T>* it = list.getHead();	
	while(it != 0) {
		Node<T>* it2 = it;
		while(it2 != 0) {
			if(it2->getNext() == 0) break;
			if(*(it2->getNext()) == *it) removeNodeAfter(it2);
			else it2 = it2->getNext();
		}
		it = it->getNext();
	}
}

int main(int arc, char** argv) {
	LinkedList<int> list;
	for(int i=0; i<10; i++) {
		list.addNode(new Node<int>(i % 3));
	}
	removeDuplicates(list);
	std::cout << list << std::endl;
	return 0;
}
