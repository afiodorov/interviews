#include <iostream>
#include "node.cpp"

template<class T>
class LinkedList{
	public:
		LinkedList() : head(0) {

		}

		LinkedList(Node<T>* node) {
			head = node;
		}

		void addNode(Node<T>* node) {
			if(head == 0) {
				head = node;
			} else {
				Node<T>* it = head;
				while(it->getNext() != 0) it = it->getNext();
				it->setNext(node);
			}
		}

		Node<T>* getHead() const {
			return head;
		}

		Node<T>* getHead() {
			return head;
		}

		void removeNode() {
			if(head == 0) return;
			Node<T>* it = head;
			while(it->getNext()->getNext() != 0)
				it = it->getNext();
			delete it->getNext();
			it->setNext(0);
		}

		std::ostream& show(std::ostream & out) const {
			if(head == 0) return out;
			Node<T>* it = head;
			while(it->getNext() != 0) {
				out << it->getData() << "->";
				it=it->getNext();
			}
			out << it->getData();
			return out;
		}

		virtual ~LinkedList() {
			if(head == 0) return;
			Node<T>* it = head;
			while(it->getNext() != 0) {
				delete it;
				it = it->getNext();
			}
			delete it;
		}

		operator const int() {
			return 0;
		}
	private:
		Node<T>* head;

};

template<class T>
std::ostream& operator <<(std::ostream& osObject, const LinkedList<T>& list)
{
    return list.show(osObject);
}

template<>
LinkedList<int>::operator const int() { 
	int result = 0;
	int pow = 1;
	Node<int>* it = getHead();
	while (it != 0) {
		result += it->getData()*pow;	
		pow*=10;
		it = it->getNext();
	}
	return result;
}
