#include <cmath>
#include <iostream>
#include "includes/smartSearchTree.cpp"
#include <string>
#include <sstream>
#include <vector>
#include <memory>

void minHeighTree() {
	// Min height BST from vector
	std::vector<int> myvector = {1, 2, 3, 4, 5, 6, 10, 11, 13};
	std::sort(myvector.begin(), myvector.end());
	Tree::SearchTree<int> tree;
	tree.insertVector(myvector, 0, myvector.size());
	std::cout << tree << std::endl
		<< "Height: " << tree.height(tree.getRoot().get()) << std::endl
		<< "Min height: " << floor(log2(myvector.size())) + 1 << std::endl;
}

int main(int, char**) {
	std::vector<int> vector;
	int n;
	std::string line;
	std::getline(std::cin, line);
	std::istringstream iss(line);
	while(iss >> n) {
		vector.push_back(n);
	}
	minHeighTree();
	
	return 0;
}
