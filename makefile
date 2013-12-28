CC      = g++
CPP_FILES := $(wildcard src/*.cpp)
OBJ_FILES := $(addprefix out/,$(notdir $(CPP_FILES:.cpp=)))
CCFLAGS  = -g -Wall -std=c++11

out/%: src/%.cpp
	   $(CC) $(CCFLAGS) -o $@ $<

all: $(OBJ_FILES)

out/addLinkedLists out/nthLinkedListElement out/removeDuplicatesLinked : src/includes/linkedlist.cpp src/includes/node.cpp

out/nthLinkedListElement : src/includes/queue.cpp

out/stacktest : src/includes/stack.cpp

out/weakPtrBlob : src/includes/Blob.h src/includes/Blobit.h

out/towers : src/includes/stackSmart.cpp

out/testQueueFromStack : src/includes/queueFromStack.cpp

out/treeShow : src/includes/smartTree.cpp

clean:
	rm out/*
