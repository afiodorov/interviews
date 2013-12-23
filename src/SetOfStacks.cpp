#include <iostream>
#include <memory>
#include <exception>
#include "includes/stackSmart.cpp"

template<typename T>
class SetOfStacks {
	public:
	static const int MAX = 2;
	SetOfStacks() : counter(0), s(std::unique_ptr<Stack<Stack<T>>>(new
				Stack<Stack<T>>())) {
		s->push(std::unique_ptr<Stack<T>>(new Stack<T>()));
	}

	void push(std::unique_ptr<T> data) {
		Stack<T> stack;
		if(counter < MAX) {
			counter++;
			stack = s->pop();
		} else {
			counter=0;
		}

		stack.push(std::move(data));
		s->push(std::unique_ptr<Stack<T>>(new Stack<T>(stack)));
	}

	T pop() {
		Stack<T> stack = s->pop();
		T ret;
		try {
			ret = stack.pop();
			s->push(std::unique_ptr<Stack<T>>(new Stack<T>(stack)));
		} catch (std::exception e) {
			stack = s->pop();
			ret = stack.pop();
			s->push(std::unique_ptr<Stack<T>>(new Stack<T>(stack)));
		}
		return ret;
	}

	private:
	int counter;
	std::unique_ptr<Stack<Stack<T>>> s;
};

int main(int arc, char** argv) {
	SetOfStacks<int> s;
	for(int i=0; i<10; i++) {
		s.push(std::unique_ptr<int>(new int(i)));
	}

	for(int i=0; i<10; i++) {
		std::cout << s.pop() << " ";
	}

	std::cout << std::endl;
	return 0;
}
