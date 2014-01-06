#include <iostream>
#include "node.cpp"

template<class T>
class LinkedList{
	public:
		LinkedList() : head(nullptr) {

		}

		LinkedList(Node<T>* node) {
			head = node;
		}

		LinkedList(const LinkedList& rhs) : head(nullptr) {
			Node<T>* node = rhs.getHead();
			while(node) {
				addNode(node);
				node = node->getNext();
			}
		}

		LinkedList(LinkedList&& rhs) : head(nullptr) {
			head = rhs.getHead();
			rhs.head = nullptr;
		}

		LinkedList& operator=(const LinkedList<T>& rhs) {
			if(head == rhs.head) return *this;
			clearNodes();
			Node<T>* node = rhs.getHead();
			while(node) {
				addNode(node);
				node = node->getNext();
			}
			return *this;
		}

		LinkedList& operator=(LinkedList<T>&& rhs) {
			if(head == rhs.head) return *this;
			clearNodes();
			head = rhs.getHead();
			rhs.head = nullptr;
			return *this;
		}

		bool isEmpty() {
			return(head == nullptr);
		}

		void addNode(Node<T>* node) {
			if(head == nullptr) {
				head = node;
			} else {
				Node<T>* it = head;
				while(it->getNext() != nullptr) it = it->getNext();
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
			if(head == nullptr) return;
			Node<T>* it = head;
			while(it->getNext()->getNext() != nullptr)
				it = it->getNext();
			delete it->getNext();
			it->setNext(nullptr);
		}

		std::ostream& show(std::ostream & out) const {
			if(head == nullptr) return out;
			Node<T>* it = head;
			while(it->getNext() != nullptr) {
				out << it->getData() << "->";
				it=it->getNext();
			}
			out << it->getData();
			return out;
		}

		virtual ~LinkedList() {
			clearNodes();
		}

		operator const int() {
			return 0;
		}

	private:
		void clearNodes() {
			if(head == nullptr) return;
			Node<T>* it = head;
			while(it->getNext() != nullptr) {
				delete it;
				it = it->getNext();
			}
			delete it;
		}

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
