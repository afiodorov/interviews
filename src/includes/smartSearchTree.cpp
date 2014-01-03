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
		};
		void insert(std::unique_ptr<T> t) {
			insertAtNode(std::unique_ptr<Node<T>>(new Node<T>(nullptr,
							std::move(t))), this->getRoot(), this->getRoot()->parent);
		}

	private:
		void insertAtNode(std::unique_ptr<Node<T>> node,
				std::unique_ptr<Node<T>>& where, Node<T> const* parent) {
			if(!where || where->data == nullptr) {
				node->parent = parent;
				where = std::move(node);
			} else if (node <= where) {
				insertAtNode(std::move(node), where->left, where.get());
			} else {
				insertAtNode(std::move(node), where->right, where.get());
			}
		}
	};
};
