#include "includes/commonblob.h"
#include "includes/Blob.h"
#include "includes/Blobit.h"

int main(int argc, char** argv) {
	Blob<std::string> b;
	std::string word;

	while(std::cin >> word) {
		if(word == "end") break;
		b.push_back(word);
	}

	for(auto entry : b) {
		std::cout << entry << std::endl;
	}
	return 0;
}
