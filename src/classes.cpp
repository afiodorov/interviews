#include <iostream>

class A {
	public:
		void virtual method() {
			std::cout << "hi from A" << std::endl;
		}
};

class B : public A {
	public:
		void method() {
			std::cout << "hi from B" << std::endl;
		}

		void onlyB() {
			std::cout << "hi from exclusive to B method. This instance is: " << instanceName << std::endl;
		}

	std::string instanceName;
};

int main() {
	A a;
	B b;
	b.instanceName = "first B instance";

	A* aPtr = &a;
	B* bPtr = &b;
	A* bAPtr = &b;
	B* aBPtr = dynamic_cast<B*>(&a);

	aPtr->method();
	bPtr->method();
	bAPtr->method();
	if(aBPtr)
		aBPtr->onlyB();
};
