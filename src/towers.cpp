#include <iostream>
#include <memory>
#include "includes/stackSmart.cpp"

template<typename T>
class MyStack : public Stack<T> {
	typedef Stack<T> super;

	public:
	virtual void push(std::unique_ptr<T>&& data) override {
		if(!super::top) super::push(std::move(data));
		else {
			if (*data >= super::peek()) {
				throw std::runtime_error(Formatter() << "Violating the tower rule");
			}
			super::push(std::forward<std::unique_ptr<T>>(data));
		}
	}
};

template<typename T>
std::ostream& operator << (std::ostream& out, const MyStack<T>& s) {
	return s.show(out);
}

template<typename T>
void transfer(int h, MyStack<T>& initial, MyStack<T>& buffer, MyStack<T>& final) {
	if(h>0) {
		transfer(h-1, initial, final, buffer);
		final.push(initial.popPtr());
		transfer(h-1, buffer, initial, final);
	}
}

int main(int, char**) {
	MyStack<int> initial, final, buffer;
	const int SIZE = 20;

	for(int i=SIZE-1; i>-1; i--) {
		initial.push(std::unique_ptr<int>(new int(i)));
	}

	std::cout << initial << std::endl;
	transfer(SIZE, initial, buffer, final);
	std::cout << final << std::endl;

	return 0;
}
