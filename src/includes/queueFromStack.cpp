#include <iostream>
#include "stackSmart.cpp"
#include <memory>

template <typename T>
class Queue {
	typedef std::unique_ptr<Stack<T>> stackPtr;
	public:
	Queue() : current(new Stack<T>()), buffer(new Stack<T>) {};
	void enqueue(std::unique_ptr<T> in) {
		current->push(std::move(in));
	}

	std::unique_ptr<T> dequeue() {
		if(buffer->isEmpty()) {
			while(!current->isEmpty()) {
				buffer->push(std::move(current->popPtr()));
			}
		}
		return std::move(buffer->popPtr());
	}

	private:
	stackPtr current, buffer;
};
