#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <utility>
#include <map>
#include <algorithm>
#include <cassert>
#include <stdio.h>
#include <execinfo.h>
#include <signal.h>
#include <stdlib.h>
#include "unistd.h"
#include <stack>
#include <limits>

// no luck with switch on strings in C++
constexpr unsigned int str2int(const char* str, int h = 0)
{
    return !str[h] ? 5381 : (str2int(str, h+1)*33) ^ str[h];
}


struct Pentomino {
	Pentomino(std::initializer_list<std::initializer_list<int>> lst) {
		for(const auto& l : lst) {
			cs.push_back(std::pair<int, int>(*l.begin(), *(l.begin()+1)));
		}
	}

	explicit Pentomino(std::vector<std::pair<int, int>>& vector) : cs(vector) {}
	explicit Pentomino(std::vector<std::pair<int, int>>&& vector) : cs(vector) {}

	std::vector<std::pair<int, int>> cs; 
	std::vector<int> serialise(std::pair<int, int> rectangle) {
		std::vector<int> result;
		for(auto pair : cs) {
			result.push_back(pair.first  + rectangle.second * pair.second);
		}
		std::sort(result.begin(), result.end());
		return result;
	}

	Pentomino flip() const {
		std::vector<std::pair<int, int>> list;
		for_each(cs.begin(), cs.end(), [&list](const std::pair<int, int>& pair) {
					list.push_back(std::pair<int, int>(pair.second, pair.first));
				});

		return Pentomino(list);
	}

	Pentomino turn90() const {
		std::vector<std::pair<int, int>> list;
		for_each(cs.begin(), cs.end(), [&list](const std::pair<int, int>& pair) {
					list.push_back(std::pair<int, int>(pair.second, -pair.first));
				});
		return Pentomino(list);
	}

	Pentomino turn180() const {
		std::vector<std::pair<int, int>> list;
		for_each(cs.begin(), cs.end(), [&list](const std::pair<int, int>& pair) {
					list.push_back(std::pair<int, int>(-pair.first, -pair.second));
				});
		return Pentomino(list);
	}

	Pentomino turn270() const {
		std::vector<std::pair<int, int>> list;
		for_each(cs.begin(), cs.end(), [&list](const std::pair<int, int>& pair) {
					list.push_back(std::pair<int, int>(-pair.second, pair.first));
				});
		return Pentomino(list);
	}

	Pentomino shift(std::pair<int, int> pair) {
		std::vector<std::pair<int, int>> list;
		for_each(cs.begin(), cs.end(), [&pair, &list](std::pair<int, int>& in) {
					list.push_back(std::pair<int, int>(in.first + pair.first,
							in.second + pair.second));
				});
		return Pentomino(list);
	}
} 
	X{{1, 0}, {0, 1}, {1, 1}, {2, 1}, {1, 2}},
	Z{{0, 0}, {1, 0}, {1, 1}, {1, 2}, {2, 2}}, 
	I{{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}}, 
	T{{0, 0}, {1, 0}, {2, 0}, {1, 1}, {1, 2}}, 
	U{{0, 0}, {2, 0}, {0, 1}, {1, 1}, {2, 1}}, 
	V{{0, 0}, {0, 1}, {0, 2}, {1, 2}, {2, 2}}, 
	W{{0, 0}, {0, 1}, {1, 1}, {1, 2}, {2, 2}}, 
	F{{1, 0}, {2, 0}, {0, 1}, {1, 1}, {1, 2}}, 
	L{{0, 0}, {1, 0}, {2, 0}, {3, 0}, {0, 1}}, 
	P{{0, 0}, {1, 0}, {2, 0}, {1, 1}, {2, 1}}, 
	N{{0, 0}, {1, 0}, {2, 0}, {2, 1}, {3, 1}}, 
	Y{{0, 0}, {1, 0}, {2, 0}, {3, 0}, {1, 1}};


class NodeBase;
struct Right {
	explicit Right(std::shared_ptr<NodeBase> ptr_)
		: ptr(ptr_) {};

	std::shared_ptr<NodeBase> ptr;
};
typedef Right Down;

struct Left{
    explicit Left(std::weak_ptr<NodeBase> ptr_)
        : ptr(ptr_) {};
    std::weak_ptr<NodeBase> ptr;
};
typedef Left Up;

class DoublyLinkedList;
class IncidenceMatrix;
class NodeColumn;

class NodeBase {
    friend DoublyLinkedList;
    friend IncidenceMatrix;
	public:
		NodeBase() : isHead(false) {}
		NodeBase(Left left_, Right right_) : 
			 left(left_.ptr), right(right_.ptr) {}

		void setHead() {
		    isHead = true;
		}

		bool getIsHead() {
		    return isHead;
		}

	virtual ~NodeBase() {};

	protected:
		std::weak_ptr<NodeColumn> column;
        std::weak_ptr<NodeBase> left, up;
		std::shared_ptr<NodeBase> right, down;
		bool isHead;
};

class NodeColumn : public NodeBase {
    public:
        NodeColumn(std::string name_) : NodeBase(), name(name_), size(0) {};
        NodeColumn(std::string name_, Left left_, Right right_)
            : NodeBase(left_, right_), name(name_), size(0) {};

		std::string getName() {
			return name;
        }

        int getSize() {
        	return size;
        }

        void increaseSize() {
        	size++;
        }

        void decreaseSize() {
        	assert(size > 0);
        	size--;
        }

	protected:
		std::string name;
		int size;
};

class DoublyLinkedList {
	friend IncidenceMatrix;
	friend inline std::ostream& operator<<(std::ostream& out, const
			DoublyLinkedList& list) {
		return list.show(out);
	}
	
    public:
        DoublyLinkedList() : firstNode(nullptr), lastNode(nullptr) {}
        std::shared_ptr<NodeBase> addRowNode(std::shared_ptr<NodeBase> node) {
            if(lastNode) {
                lastNode->right = node;
                node->left = lastNode;
                lastNode = lastNode->right;
            } else {
                firstNode = lastNode = node;
            }
            firstNode->left = lastNode;
            return lastNode;
        }
    private:
        std::shared_ptr<NodeBase> firstNode; 
        std::shared_ptr<NodeBase> lastNode; 

		std::ostream& show(std::ostream& out) const {
        	auto node = firstNode;

        	while(node) {
        		out << node->column.lock()->getName() << " ";
        		node = node->right;
        	}
        	return out << std::endl;
        }
};

class IncidenceMatrix {
	public:
		IncidenceMatrix(std::pair<int, int> rectangle) : rectangle(rectangle) {
			createHeader();
			fillIn();
		}

		std::shared_ptr<NodeBase> findColumnWithLeastOnes() {
			int min = std::numeric_limits<int>::max();
			std::shared_ptr<NodeBase> minColumn = nullptr;

			std::shared_ptr<NodeBase> column = headerRow.firstNode;
			while(column) {
				if(column->column.lock()->getSize() < min) minColumn = column;
				column = column->right;
			}
			return minColumn;
		}

		void addRow(DoublyLinkedList row) {
			auto node = row.firstNode;
			while(node) {
				assert(!node->column.expired());

				node->column.lock()->increaseSize();
				auto nodeAbove = node->column.lock()->up;
				node->up = nodeAbove;
				nodeAbove.lock()->down = node;
				node->column.lock()->up = node;
				node = node->right;
			}
		}

		void cover(std::shared_ptr<NodeBase> column) {
			if(column->right)
				column->right->left = column->left;

			assert(!column->left.expired());
			column->left.lock()->right = column->right;
			std::shared_ptr<NodeBase> row = column->down;
			while(row) {
				std::shared_ptr<NodeBase> runner = row;
				while(runner) {
					assert(!runner->up.expired());
					runner->up.lock()->down = runner->down;
					runner->down = runner->up.lock();
				}
				column->column.lock()->decreaseSize();
			}
		}

	private:
		std::map<std::string, Pentomino> shapes;
		void createHeader() {
			shapes = {{"X", X}, {"Z", Z}, {"I", I}, {"T", T}, {"U", U},
					{"V", V}, {"W", W}, {"F", F}, {"L", L}, {"P", P}, {"N", N},
					{"Y", Y}};

			auto headNode = std::shared_ptr<NodeColumn>(new NodeColumn("head"));
			headNode->column = headNode;
			headNode->up = headNode;
			headNode->setHead();
			headerRow.addRowNode(headNode);
			map["head"] = headNode;

			for(int i = 0; i < rectangle.first * rectangle.second; i++) {
				std::string currentName  = std::to_string(i);
				auto columnNode = std::shared_ptr<NodeColumn>(new NodeColumn(currentName));
				columnNode->column = columnNode;
				columnNode->up = columnNode;
				headerRow.addRowNode(columnNode);
				map[currentName] = columnNode;
			}

			for(auto shape : shapes) {
				auto columnNode = std::shared_ptr<NodeColumn>(new NodeColumn(shape.first));
				columnNode->column = columnNode;
				columnNode->up = columnNode;
				headerRow.addRowNode(columnNode);
				map[shape.first] = columnNode;
			}
		}
		std::map<std::string, std::shared_ptr<NodeColumn>> map;
		DoublyLinkedList headerRow;
		std::pair<int,int> rectangle;

		void fillIn() {
			for(auto shape : shapes) {
				std::stack<Pentomino> stack;
				generateAllShapes(shape, stack);

				while(!stack.empty()) {
					auto pentomino = stack.top();
					stack.pop();

					int x = 0;
					while(x < rectangle.first) {
						int y = 0;
						while(y < rectangle.second) {
							Pentomino movedPentomino = pentomino.shift({x, y});
							std::vector<int> shapeSerialised;
							bool isFitted =
								std::accumulate(movedPentomino.cs.begin(),
									movedPentomino.cs.end(), true,
										[this, &shapeSerialised](bool result, std::pair<int, int>& pair) {
										shapeSerialised.push_back(pair.first + pair.second * rectangle.first);

										return result && (pair.first > -1) && (pair.second > -1)
											&& (pair.first < rectangle.first)
											&& (pair.second < rectangle.second);
									});
					 		y++;
							if(!isFitted) continue;

							std::sort(shapeSerialised.begin(), shapeSerialised.end());
							DoublyLinkedList list;
							for_each(shapeSerialised.begin(), shapeSerialised.end(), 
									[&list, this](int& integer) {
								std::string str = std::to_string(integer);
								auto node = std::shared_ptr<NodeBase>(new NodeBase);
								node->column = map[str];
								assert(!node->column.expired());
								list.addRowNode(node);
							});
							auto node = std::shared_ptr<NodeBase>(new NodeBase);
							node->column = map[shape.first];
							assert(!node->column.expired());
							list.addRowNode(node);
							addRow(list);
						}
						x++;
					}
				}
			}
		}

		void generateAllShapes(const std::pair<std::string, Pentomino>& shape, 
			std::stack<Pentomino>& stack) {
			switch(str2int(shape.first.c_str())) {
				case str2int("L"):
					;
				case str2int("N"):
					;
				case str2int("P"):
					;
				case str2int("F"):
					;
				case str2int("Y"):
					stack.push(shape.second.flip());
					stack.push(shape.second.flip().turn90());
					stack.push(shape.second.flip().turn180());
					stack.push(shape.second.flip().turn270());
				case str2int("V"):
					;
				case str2int("W"):
					;
				case str2int("T"):
					;
				case str2int("U"):
					stack.push(shape.second);
					stack.push(shape.second.turn90());
					stack.push(shape.second.turn180());
					stack.push(shape.second.turn270());
				break;

				case str2int("Z"):
					stack.push(shape.second.flip());
					stack.push(shape.second.flip().turn90());
				case str2int("I"):
					stack.push(shape.second.turn90());
				case str2int("X"):
					stack.push(shape.second);
				break;
			}
		}
};

int solve(std::pair<int,int> rectangle, bool shouldShow = false) {
    IncidenceMatrix matrix(rectangle);
    return 1;
}

void applyKnuthAlgo(IncidenceMatrix& matrix) {

}

void handler(int sig) {
  void *array[10];
  size_t size;

  // get void*'s for all entries on the stack
  size = backtrace(array, 10);

  // print out all the frames to stderr
  fprintf(stderr, "Error: signal %d:\n", sig);
  backtrace_symbols_fd(array, size, STDERR_FILENO);
  exit(1);
}

int main(int, char**) {
	signal(SIGSEGV, handler);
	solve({6,10});
	return 0;
}
