#include <iostream>

template<class T>
class Node {
	public:
	Node() : next(nullptr) {
		data = new T();
	}

	Node(const T& node) : next(nullptr) {
		data = new T(node);
	}

	Node(T&& node) : next(nullptr) {
		data = new T(std::forward<T>(node));
	}

	virtual ~Node() {
		delete data;
	}

	Node& operator= (const Node& rhs) {
		data = rhs.data;
		next = rhs.getNext();
		return *this;
	}

	bool operator== (const Node& rhs) const {
		return (this->getData() == rhs.getData());
	}

	Node* getNext() const {
		return next;
	}

	void setNext(Node* in) {
		next = in;
	}

	const T& getData() const {
		return *data;
	}

	T& getData() {
		return *data;
	}

	std::ostream& show(std::ostream& out) const {
		out << getData();
		return out;
	}
	
	private:
	T* data;
	Node* next;
};

template<class T>
std::ostream& operator << (std::ostream& out, const Node<T>& node){
	return node.show(out);
}
