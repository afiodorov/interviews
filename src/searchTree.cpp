#include <cmath>
#include <iostream>
#include "includes/smartSearchTree.cpp"
#include "includes/linkedlist.cpp"
#include <string>
#include <sstream>
#include <vector>
#include <memory>

void minHeightTree() {
	// Min height BST from vector
	std::vector<int> myvector = {1, 2, 3, 4, 5, 6, 10, 11, 13};
	std::sort(myvector.begin(), myvector.end());
	Tree::SearchTree<int> tree;
	tree.insertVector(myvector, 0, myvector.size());
	std::cout << tree << std::endl
		<< "Height: " << tree.height(tree.getRoot().get()) << std::endl
		<< "Min height: " << floor(log2(myvector.size())) + 1 << std::endl;
}

template<typename T>
void buildLinkedLists(Tree::SearchTree<T>& tree) {
	LinkedList<Tree::Node<T>> list;
	list.addNode(new Node<Tree::Node<T>>(std::move(tree.getRoot())));

	while(!list.isEmpty()) {
		std::cout << list << std::endl;
		list = buildLinkedList(list);
	}
}

template<typename T>
LinkedList<Tree::Node<T>> buildLinkedList(LinkedList<Tree::Node<T>>& list) {
	LinkedList<Tree::Node<T>> newList;
	Node<Tree::Node<T>>* node = list.getHead();
	while(node) {
		if(node->getData().isLeft())
			newList.addNode(
					new Node<Tree::Node<T>>(std::move(node->getData().
							takeLeft())));
		if(node->getData().isRight())
			newList.addNode(
					new Node<Tree::Node<T>>(std::move(node->getData().
							takeRight())));
		node = node->getNext();
	}
	return newList;
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
	Tree::SearchTree<int> tree(vector);
	buildLinkedLists(tree);
	// minHeightTree();
	
	return 0;
}
