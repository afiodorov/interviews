#include <iostream>
#include <memory>
#include <vector>
#include <stack>

namespace Tree {
	template<typename> class Tree;
	template<typename T>

	class Node {
		friend class Tree<T>;
		public:
		Node(Node<T> const* const &parent_, std::unique_ptr<T> data_) :
			right(nullptr), left(nullptr), parent(parent_),
			data(std::move(data_)) {}

		Node(Node<T> const* const &parent_) :
			right(nullptr), left(nullptr), parent(parent_), 
			data(nullptr) {}

		void setRight(std::unique_ptr<Node<T>> right) {
			this->right = std::move(right);
		}

		void setLeft(std::unique_ptr<Node<T>> left) {
			this->left = std::move(left);
		}

		void setData(std::unique_ptr<T> data) {
			this->data = std::move(data);
		}

		T getData() const {
			return *data;	
		}

		private:
		Node(const Node&) {}
		void operator=(const Node&) {}

		std::unique_ptr<Node<T>> right;
		std::unique_ptr<Node<T>> left;
		Node<T> const* parent;
		std::unique_ptr<T> data;

	};

	template<typename T>
	class Tree {
		public:
		Tree() : root(std::unique_ptr<Node<T>>(new Node<T>(nullptr))) {}
		Tree(const std::vector<T>& vector) :
			root(std::unique_ptr<Node<T>>(new Node<T>(nullptr,
					std::unique_ptr<T>(new T(vector[0]))))) {
			addChildren(root, vector, 0);
		}

		std::ostream& show(std::ostream& out) const {
			showNode(out, root);
			return out;
		}

		std::ostream& showPreOrder(std::ostream& out) const {
			std::stack<Node<T> const*> stack;
			Node<T> const* node = root.get();

			while((!stack.empty()) || (node != nullptr)) {
				if(node != nullptr) {
					out << node->getData() << " ";
					stack.push(node);
					node = node->left.get();
				} else {
					node = stack.top();
					stack.pop();
					node = node->right.get();
				}
			}
			return out;
		}

		private:
		std::unique_ptr<Node<T>> root;

		void addChildren(std::unique_ptr<Node<T>> const &parent,
				const std::vector<T>& vector, 
				typename std::vector<T>::size_type index) {

			const typename std::vector<T>::size_type leftIndex = (index + 1) * 2 - 1;
			const typename std::vector<T>::size_type rightIndex = (index + 1) * 2;

			if(leftIndex < vector.size()) {
				parent->setLeft(std::unique_ptr<Node<T>>(new Node<T>(parent.get(),
						std::unique_ptr<T>(new T(vector[leftIndex])))));
				addChildren(parent->left, vector, leftIndex);
			}

			if(rightIndex < vector.size()) {
				parent->setRight(std::unique_ptr<Node<T>>(new Node<T>(parent.get(),
						std::unique_ptr<T>(new T(vector[rightIndex])))));
				addChildren(parent->right, vector, rightIndex);
			}

		}

		void showNode(std::ostream& out, std::unique_ptr<Node<T>> const &node) const {
					if(node->left) showNode(out, node->left);
			out << node->getData() << " ";
					if(node->right) showNode(out, node->right);
		}
	};

}

template<typename T>
std::ostream& operator<<(std::ostream& out, const Tree::Tree<T>& tree) {
	return tree.show(out);
}
