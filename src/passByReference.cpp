#include <iostream>
#include <string>
class A {
	public:
	A(std::string name_) : name( name_ ) {}
	virtual ~A() {
		std::cout << name << " deleted" << " " << this << std::endl;
	}
	std::string getName() const { return name; }

	A& operator=(const A &rhs) {
		this->name = rhs.getName();
		return *this;
	}

	private:
	std::string name;
};

void change(A& a) {
	// a = new A("changed");
	a = A("changed");
}

int main() {
	A a("dog");
	std::cout << a.getName() << " " << &a << std::endl;
	change(a);
	std::cout << a.getName() << " " << &a << std::endl;
	std::cout << "return a reference" << std::endl;
	A b(a);
	std::cout << b.getName() << " " << &b << std::endl;
	return 0;
}
