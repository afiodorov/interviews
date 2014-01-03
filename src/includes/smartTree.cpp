#include <iostream>
#include <memory>
#include <vector>
#include <stack>

namespace Tree {
	template<typename> class Tree;
	template<typename> class SearchTree;

	template<typename T>
	class Node {
		friend inline std::ostream& operator<<(std::ostream& out, const Node& node) {
			return out << node.getData();
		}
		friend class Tree<T>;
		friend class SearchTree<T>;

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

		bool operator<(const Node<T>& rhs) {
			return *data < *rhs.data();
		}

		bool operator>(const Node<T>& rhs) {
			return *data > *rhs.data();
		}

		bool operator>=(const Node<T>& rhs) {
			return !operator<(rhs);
		}

		bool operator<=(const Node<T>& rhs) {
			return !operator>(rhs);
		}

		bool operator==(const Node<T>& rhs) {
			return (*data == *rhs.data());
		}

		bool operator!=(const Node<T>& rhs) {
			return !operator==(rhs);
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
		friend inline std::ostream& operator<<(std::ostream& out, const Tree& tree) {
			return tree.showInOrder(out, tree.root);
		}

		public:
		Tree() : root(std::unique_ptr<Node<T>>(new Node<T>(nullptr))) {}
		Tree(const std::vector<T>& vector) :
			root(std::unique_ptr<Node<T>>(new Node<T>(nullptr,
					std::unique_ptr<T>(new T(vector[0]))))) {
			addChildren(root, vector, 0);
		}

		bool isBalanced() const {
			return isBalanced(getRoot());
		}

		std::ostream& showPreOrderIter(std::ostream& out) const {
			std::stack<Node<T> const*> stack;
			Node<T> const* node = root.get();

			while((!stack.empty()) || (node != nullptr)) {
				if(node != nullptr) {
					out << *node << " ";
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

		std::ostream& showPreOrderNoStack(std::ostream& out) const {
			Node<T> const* lastNode = nullptr;
			Node<T> const* node = root.get();

			while(node) {
				if (lastNode == node->parent) {
					out << *node << " ";

					if (node->left) {
						lastNode = node;
						node = node->left.get();
						continue;
					} else {
						lastNode = nullptr;
					}
				}

				if (lastNode == node->left.get()) {
					if (node->right) {
						lastNode = node;
						node = node->right.get();
						continue;
					} else {
						lastNode = nullptr;
					}
				}

				if (lastNode == node->right.get()) {
					lastNode = node;
					node = node->parent;
				}
			}

			return out;
		}

		std::ostream& showInOrderNoStack(std::ostream& out) const {
			Node<T> const* lastNode = nullptr;
			Node<T> const* node = root.get();

			while(node) {
				if (lastNode == node->parent) {
					if (node->left) {
						lastNode = node;
						node = node->left.get();
						continue;
					} else {
						lastNode = nullptr;
					}
				}

				if (lastNode == node->left.get()) {
					out << *node << " ";

					if (node->right) {
						lastNode = node;
						node = node->right.get();
						continue;
					} else {
						lastNode = nullptr;
					}
				}

				if (lastNode == node->right.get()) {
					lastNode = node;
					node = node->parent;
				}
			}
			return out;
		}

		std::ostream& showInOrder(std::ostream& out, std::unique_ptr<Node<T>> const &node) const {
			if(node->left) showInOrder(out, node->left);
			out << *node << " ";
			if(node->right) showInOrder(out, node->right);
			return out;
		}

		std::ostream& showPreOrder(std::ostream& out, std::unique_ptr<Node<T>> const &node) const {
			out << *node << " ";
			if(node->left) showPreOrder(out, node->left);
			if(node->right) showPreOrder(out, node->right);
			return out;
		}

		std::ostream& showPostOrder(std::ostream& out, std::unique_ptr<Node<T>> const &node) const {
			if(node->left) showPostOrder(out, node->left);
			if(node->right) showPostOrder(out, node->right);
			out << *node << " ";
			return out;
		}

		Node<T> const* getRoot() const {
			return root.get();
		}

		std::unique_ptr<Node<T>> getRoot() {
			return root;
		}

		protected:
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

		bool isBalanced(Node<T> const* const node) const {
			if (!node) return true;
			return (abs(height(node->right.get()) - height(node->left.get())) <= 1) &&
					isBalanced(node->left.get()) && isBalanced(node->right.get());
		}

		int height(Node<T> const* const node) const {
			if(!node) return 0;
			return std::max(height(node->right.get()), height(node->left.get())) + 1;
		}
	};
}
