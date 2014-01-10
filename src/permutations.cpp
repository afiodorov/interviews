#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <list>

std::vector<std::string> getAllPermutations(const std::string& input, size_t size) {
	if(input.size() == 0) return {};

	if(size == 1) {
		return {input};
	}

	std::vector<std::string> newPermutations;
	for(auto str : getAllPermutations(input, size-1)) {
			auto element = input[size-1];
			for(size_t i=0; i<size; i++) {
				std::stringstream stream;
				size_t j = 0;
				while(j<i) {
					stream << str[j];
					j++;
				}
				stream << element;
				while(j<size-1) {
					stream << str[j];
					j++;
				}
				newPermutations.push_back(stream.str());
			}
	}

	return newPermutations;
}

int factorial(int in) {
	std::list<int> l(in);
    std::iota(l.begin(), l.end(), 1);
	return std::accumulate(l.begin(), l.end(), 1, 
			[](int prod, int a){return prod*a;});
}

int main(int argc, char** argv) {
	if(argc < 2) return 1;

	std::string input(argv[1]);

	int counter = 0;
	for(auto str : getAllPermutations(input, input.size())) {
		std::cout << str << std::endl;
		counter++;
	}

	std::cout << "Found: " << counter << ". Expected: " <<
		factorial(input.size()) << "." << std::endl;

	return 0;
}
