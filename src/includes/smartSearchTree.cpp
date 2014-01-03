#include <memory>
#include "smartTree.cpp"

namespace Tree{
	template<typename T>
	class SearchTree : public Tree<T> {
		friend inline std::ostream& operator<<(std::ostream& out, const
				SearchTree& tree) {
			return tree.showInOrder(out, tree.root);
		}

	public:
		void insert(std::unique_ptr<Node<T>> node) {
			insertAtNode(node, this->getRoot());
		}

	private:
		void insertAtNode(std::unique_ptr<Node<T>> node,
				std::unique_ptr<Node<T>> where) {
			if(!where) {
				where = std::move(node);
			} else if (node <= where) {
				insertAtNode(node, where->left);
			} else {
				insertAtNode(node, where->right);
			}
		}
	};
};
