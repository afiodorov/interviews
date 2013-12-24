#include <iostream>
#include <memory>
#include <exception>

template<typename T>
class Node {
	public:
	std::shared_ptr<Node> previous;
	Node(std::unique_ptr<T> data_) : previous(nullptr), data(std::move(data_)) {};

	operator T() {
		return *data;
	}
	private:
	std::unique_ptr<T> data;
};

template<typename T>
class Stack {
	public:
	Stack() : top(nullptr) {};
	virtual T pop() {
		if(!top) throw std::exception();

		std::shared_ptr<Node<T>> node = top;
		top = top->previous;
		return *node;
	};

	virtual void push(std::unique_ptr<T> data) {
		auto node = std::shared_ptr<Node<T>>(new Node<T>(std::move(data)));
		node->previous = top;
		top = node;
	}

	virtual T peek() const {
		if(!top) throw std::exception();
		return *top;
	}
	
	virtual bool isEmpty() const {
		return top == nullptr;	
	}

	std::ostream& show(std::ostream& out) const {
		auto node = top;
		while(node != nullptr) {
			out << *node << " ";
			node = node->previous;
		}
		return out;
	}

	protected:
	std::shared_ptr<Node<T>> top;
};

template<typename T>
std::ostream& operator << (std::ostream& out, const Stack<T>& s) {
	return s.show(out);
}
