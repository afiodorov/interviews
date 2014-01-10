#include <iostream>
#include <cmath>

double iterate(double x, const double& a) {
	return (x + a / x) / 2;
}

int main(int, char**) {
	std::cout.precision(10);
	double root;
	std::cin >> root;

	const double err = 1/100;
	double myRoot0 = iterate(1, root);
	double myRoot1 = iterate(myRoot0, root);

	while(abs(myRoot1*myRoot1 - root) > err*err) {
		double buff = myRoot1;
		myRoot1 = iterate(myRoot0, root);
		myRoot0 = buff;
	}
	
	std::cout << "Result: " << myRoot1 << std::endl;
	std::cout << "Actual sq root: " << sqrt(root) << std::endl;

	return 0;
}
