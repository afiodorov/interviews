CC      = g++
CPP_FILES := $(wildcard src/*.cpp)
OBJ_FILES := $(addprefix out/,$(notdir $(CPP_FILES:.cpp=)))
CCFLAGS  = -g -Wall -std=c++11

out/%: src/%.cpp
	   $(CC) $(CCFLAGS) -o $@ $<

all: $(OBJ_FILES)

release: CCFLAGS = -Ofast -std=c++11
release: out/pentimo

out/addLinkedLists out/nthLinkedListElement out/removeDuplicatesLinked : src/includes/linkedlist.cpp src/includes/node.cpp

out/nthLinkedListElement : src/includes/queue.cpp

out/stacktest : src/includes/stack.cpp

out/weakPtrBlob : src/includes/Blob.h src/includes/Blobit.h

out/towers : src/includes/stackSmart.cpp

out/testQueueFromStack : src/includes/queueFromStack.cpp

out/treeShow : src/includes/smartTree.cpp

out/searchTree : src/includes/smartSearchTree.cpp src/includes/smartTree.cpp src/includes/node.cpp src/includes/linkedlist.cpp

out/heapSort : src/includes/heap.cpp

clean:
	rm out/*
