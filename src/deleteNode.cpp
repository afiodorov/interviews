#include <iostream>
#include "includes/linkedlist.cpp" 

template<class T>
void removeNode(Node<T>* const& node) {
	if (node == 0 || node->getNext() == 0) 
		throw new std::exception();
	*node = *(node->getNext());
}

int main(int arc, char** argv) {
	LinkedList<int> list;
	for(int i=0; i<10; i++) list.addNode(new Node<int>(i));
	Node<int>* pNode = new Node<int>(10);
	list.addNode(pNode);
	for(int i=11; i<20; i++) list.addNode(new Node<int>(i));
	std::cout << list << std::endl;
	std::cout << "Removing " << *pNode << std::endl;
	removeNode(pNode);
	std::cout << list << std::endl;
}
