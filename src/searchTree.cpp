#include <iostream>
#include "includes/smartSearchTree.cpp"
#include <string>
#include <sstream>
#include <vector>
#include <memory>

int main(int, char**) {
	std::vector<int> vector;
	int n;
	std::string line;
	std::getline(std::cin, line);
	std::istringstream iss(line);
	while(iss >> n) {
		vector.push_back(n);
	}
	Tree::SearchTree<int> tree(vector);
	tree.insert(std::unique_ptr<int>(new int(5)));
	std::cout << tree;

	return 0;
}
