#include <iostream>
#include <memory>

typedef std::shared_ptr<int> sArr;

namespace size {
	const int N = 30;
	static int counter(0);
};

class Stack {
	public:
	Stack(sArr& arr_) : arr(arr_), index(0), counter(0),
		shift( (size::counter++) * (size::N/3) ) { };

	Stack(sArr&& arr_) : arr(std::move(arr_)), index(0), counter(0),
		shift( (size::counter++) * (size::N/3) ) {};

	void push(int a) {
		*(arr.get() + index + shift) = a;
		index = (index + 1 + size::N/3) % (size::N/3);
		counter++;
	}

	int pop() {
		if(--counter < 0) throw std::exception();
		int ret = *(arr.get() + (index-1 + size::N/3) % (size::N/3) + shift);
		index = (index - 1 + size::N/3) % (size::N/3);
		return ret; 
	}

	std::ostream& show(std::ostream& out) const {
		for(int k = 0; k<size::N/3; k++) {
			out << *(arr.get() + ((index - k - 1 + size::N/3) % (size::N/3)) +
					shift) << " ";
		}
		return out;
	}

	sArr& getArr() {
		return arr;
	}

	virtual ~Stack() {
		size::counter--;
	}

	private:
	sArr arr;
	int index;
	int counter;
	const int shift;
};

std::ostream& operator<< (std::ostream& out, const Stack& s) {
	return s.show(out);
}

int main(int argc, char** argv) {
	Stack s1(sArr(new int[size::N], [](int *p){delete[] p;}));
	for(int i=0; i<10; i++) {
		s1.push(i);
	}
	std::cout << s1.pop() << std::endl;

	Stack s2(s1.getArr());
	for(int i=0; i<10; i++) {
		s2.push(i + 10);
	}
	std::cout << s2.pop() << std::endl;
	std::cout << s1.pop() << std::endl;

	Stack s3(s1.getArr());
	for(int i=0; i<10; i++) {
		s3.push(i + 20);
	}
	std::cout << s2.pop() << std::endl;
	std::cout << s3.pop() << std::endl;
	s2.push(11);
	std::cout << s3.pop() << std::endl;
	std::cout << s2.pop() << std::endl;

	return 0;
}
