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
	T pop() {
		if(!top) throw std::exception();

		std::shared_ptr<Node<T>> node = top;
		top = top->previous;
		return *node;
	};

	void push(std::unique_ptr<T> data) {
		auto node = std::shared_ptr<Node<T>>(new Node<T>(std::move(data)));
		node->previous = top;
		top = node;
	}

	T peek() const {
		if(!top) throw std::exception();
		return *top;
	}

	private:
	std::shared_ptr<Node<T>> top;
};
