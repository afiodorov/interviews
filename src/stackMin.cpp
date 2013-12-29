#include <iostream>

class StackNode {
	public:
		StackNode* previous;
		int min;
		StackNode(int a) : previous(0), min(a), data(a) {}

		operator int() {
			return data;
		}
	private:
		int data;
};

class Stack {
	public:
		Stack() : top(nullptr) {}
		void push(int a) {
			if(!top) top = new StackNode(a);
			else {
				auto node = new StackNode(a);
				node->previous = top;
				top = node;
				node->min = (a < node->previous->min) ? a :
					node->previous->min; 
			}
		}

		int pop() {
			if(top) {
				auto node = top;
				top = node->previous;
				delete node;
				return *top;
			}
			throw std::exception();
			return 0;
		};

		int peek() const {
			if(top) {
				return *top;
			}
			throw std::exception();
			return 0;
		}

		int min() {
			if(top) {
				return top->min;
			}
			throw std::exception();
			return 0;
		}

	private:
		StackNode* top;
};

int main(int argc, char** argv) {
	Stack stack;
	for(int i=10; i>0; i--) {
		stack.push(i);
		if (i%3 == 0) stack.push(6);
		if (i%6 == 0) stack.pop();
		std::cout << stack.min() << std::endl;
	}

	stack.pop();
	stack.pop();
	std::cout << stack.min() << std::endl;

	return 0;
}
