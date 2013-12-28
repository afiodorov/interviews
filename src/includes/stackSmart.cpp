#include <iostream>
#include <memory>
#include <exception>
#include <stdexcept>
#include <sstream>

class Formatter
{
public:
    Formatter() {}
    ~Formatter() {}

    template <typename Type>
    Formatter & operator << (const Type & value)
    {
        stream_ << value;
        return *this;
    }

    std::string str() const         { return stream_.str(); }
    operator std::string () const   { return stream_.str(); }

    enum ConvertToString 
    {
        to_str
    };
    std::string operator >> (ConvertToString) { return stream_.str(); }

private:
    std::stringstream stream_;

    Formatter(const Formatter &);
    Formatter & operator = (Formatter &);
};

template<typename T>
class Node {
	public:
	std::shared_ptr<Node> previous;
	explicit Node(std::unique_ptr<T>&& data_) : previous(nullptr), data(std::move(data_)) {};

	T getData() const {
		return *data;
	}

	std::unique_ptr<T> movePtr() {
		return std::move(data);
	}

	private:
	Node(const Node&);
	Node& operator=(const Node&);
	std::unique_ptr<T> data;
};

template<typename T>
class Stack {
	public:
	Stack() : top(nullptr) {};
	virtual T pop() {
		if(!top) throw std::runtime_error(Formatter() << "Stack is empty");

		std::shared_ptr<Node<T>> node = top;
		top = top->previous;
		return node->getData();
	};

	virtual std::unique_ptr<T> popPtr() {
		if(!top) throw std::runtime_error(Formatter() << "Stack is empty");

		std::shared_ptr<Node<T>> node = top;
		top = top->previous;
		return node->movePtr();
	};

	virtual void push(std::unique_ptr<T>&& data) {
		auto node = std::shared_ptr<Node<T>>(new
				Node<T>(std::forward<std::unique_ptr<T>>(data)));
		node->previous = top;
		top = node;
	}

	virtual T peek() const {
		if(!top) throw std::runtime_error(Formatter() << "Stack is empty");
		return top->getData();
	}
	
	virtual bool isEmpty() const {
		return top == nullptr;	
	}

	std::ostream& show(std::ostream& out) const {
		auto node = top;
		while(node != nullptr) {
			out << node->getData() << " ";
			node = node->previous;
		}
		return out;
	}

	protected:
	std::shared_ptr<Node<T>> top;
};

template<typename T>
std::ostream& operator << (std::ostream& out, const Stack<T>& s) {
	return s.show(out);
}
