#include <iostream>
#include "includes/smartTree.cpp"
#include <vector>
#include <string>
#include <sstream>

int main (int, char**) {
	std::vector<int> vector;
	int a;
	std::string line;
	std::getline(std::cin, line);
	std::istringstream iss(line);
	while(iss >> a) {
		vector.push_back(a);
	}

	Tree::Tree<int> tree = Tree::Tree<int>(vector);
	std::cout << tree;
	std::cout << tree.isBalanced();
	return 0;
}
