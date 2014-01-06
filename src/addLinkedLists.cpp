#include <iostream>
#include "includes/linkedlist.cpp" 

template<class T>
LinkedList<T> addLinkedLists(const LinkedList<T>& l1, const LinkedList<T>& l2){
	LinkedList<T> result;
	Node<T> *it1 = l1.getHead(), *it2 = l2.getHead();
	T carryover = 0;
	while(it1 !=0 || it2 != 0) {
		T n1 = (it1 != 0) ? it1->getData() : 0;
		T n2 = (it2 != 0) ? it2->getData() : 0;
		T n = n1 + n2 + carryover;
		result.addNode(new Node<T>(n % 10));
		carryover = n / 10;
		it1 = (it1 != 0) ? it1->getNext() : 0;
		it2 = (it2 != 0) ? it2->getNext() : 0;
	}

	while(carryover > 0) {
		result.addNode(new Node<T>(carryover % 10));
		carryover/=10;
	}
	return result;
}

int main(int, char**) {
	std::cout.setf(std::ios::boolalpha);
	LinkedList<int> l1, l2;
	l1.addNode(new Node<int>(9));
	l1.addNode(new Node<int>(9));
	l1.addNode(new Node<int>(9));

	l2.addNode(new Node<int>(9));
	l2.addNode(new Node<int>(9));
	l2.addNode(new Node<int>(9));
	l2.addNode(new Node<int>(9));

	LinkedList<int> res = addLinkedLists(l1, l2);

	std::cout << "Adding " << (int) l1 << std::endl;
	std::cout << "and " << (int) l2 << std::endl;
	std::cout << "Result: " << (int) res << ". Right: " <<
		((int) res == ((int) l1 + (int) l2)) << std::endl;

	return 0;
}
