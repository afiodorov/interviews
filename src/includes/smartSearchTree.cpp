#include <memory>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include "smartTree.cpp"

namespace Tree{
	template<typename T>
	class SearchTree : public Tree<T> {
		friend inline std::ostream& operator<<(std::ostream& out, const
				SearchTree& tree) {
			return tree.showInOrder(out, tree.root);
		}

	public:
		SearchTree(const std::vector<T>& vector) {
			std::srand ( unsigned ( std::time(0) ) );
			std::vector<T> myvector(vector);
			std::random_shuffle(myvector.begin(), myvector.end());
			for(auto elem : myvector) {
				insert(std::unique_ptr<T>(new T(elem)));
			}
		}

		SearchTree() : Tree<T>() {}

		void insert(std::unique_ptr<T> t) {
			insertAtNode(std::unique_ptr<Node<T>>(new Node<T>(nullptr,
							std::move(t))), this->getRoot(), this->getRoot()->parent);
		}

		std::unique_ptr<Node<T>> remove(Node<T> const* node) {
			if(!node) return nullptr;
			auto& toBeRemoved = findSubTree(node, this->getRoot());
			auto& owner = this->getRoot();
			if(!toBeRemoved) return nullptr;
			if(!toBeRemoved->left && !toBeRemoved->right) {
				return std::move(toBeRemoved);
			} else if (toBeRemoved->left && !toBeRemoved->right) {
				auto toBeReturned = std::move(toBeRemoved);
				insertAtNode(std::move(toBeReturned->left), owner,
					toBeReturned->parent);
				return toBeReturned;
			} else if (toBeRemoved->right && !toBeRemoved->left) {
				auto toBeReturned = std::move(toBeRemoved);
				insertAtNode(std::move(toBeReturned->right), owner,
					toBeReturned->parent);
				return toBeReturned;
			} else {
				auto successor = this->remove(this->successor(*toBeRemoved));
				successor->left = std::move(toBeRemoved->left);
				successor->right = std::move(toBeRemoved->right);
				auto toBeReturned = std::move(toBeRemoved);
				insertAtNode(std::move(successor), owner, toBeReturned->parent);
				return toBeReturned;
			}
		}

		Node<T> const* find(std::unique_ptr<T> t) {
			return findSubTree(std::move(t), this->getRoot());
		}

		Node<T> const* successor(const Node<T>& node) {
			if(node.right) return min(node.right);
			else {
				Node<T> const* nodePtr = &node;
				Node<T> const* parent = nodePtr->parent;
				while(parent && (nodePtr != parent->left.get())) {
					nodePtr = parent;
					parent = nodePtr->parent;
				}
				return parent;
			}
		}

		void insertVector(std::vector<T>& vector,
				typename std::vector<T>::size_type b,
				typename std::vector<T>::size_type e) {
			if(b >= e) return;
			typename std::vector<T>::size_type middle = b + (e - b)/2;
			insert(std::unique_ptr<T>(new T(vector[middle])));
			insertVector(vector, b, middle);
			insertVector(vector, middle + 1, e);
		}


		Node<T> const* min(const std::unique_ptr<Node<T>>& node) {
			if(!node->left) return node.get();
			else return min(node->left);
		}


	private:
		void insertAtNode(std::unique_ptr<Node<T>> node,
				std::unique_ptr<Node<T>>& where, Node<T>* parent) {
			if(!where || where->data == nullptr) {
				node->parent = parent;
				where = std::move(node);
			} else if (*node <= *where) {
				insertAtNode(std::move(node), where->left, where.get());
			} else {
				insertAtNode(std::move(node), where->right, where.get());
			}
		}

		Node<T> const* findSubTree(std::unique_ptr<T> what, const
				std::unique_ptr<Node<T>>& where) const {
			if(!where || !where->getData()) return nullptr;

			if(where->getData() == *what) {
				return where.get();
			} else if (*what < where->getData()) {
				return findSubTree(std::move(what), where->left);
			} else {
				return findSubTree(std::move(what), where->right);
			}
		}

		std::unique_ptr<Node<T>>& findSubTree(Node<T> const* node,
				std::unique_ptr<Node<T>>& where) {
			if(*node <= *where.get()) {
				if(*node == *where.get()) return where;
				if(*node == *where->left.get()) return where->left;
				return findSubTree(node, where->left);
			} else {
				if(*node == *where->right.get()) return where->right;
				return findSubTree(node, where->right);
			}
		}
	};
};
