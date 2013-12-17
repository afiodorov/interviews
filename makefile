CC      = g++
CPP_FILES := $(wildcard src/*.cpp)
OBJ_FILES := $(addprefix out/,$(notdir $(CPP_FILES:.cpp=)))
CCFLAGS  = -g -Wall -std=c++11

out/%: src/%.cpp
	   $(CC) $(CCFLAGS) -o $@ $<

executable: $(OBJ_FILES)

clean:
	rm out/*
