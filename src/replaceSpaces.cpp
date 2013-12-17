#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <sstream>

std::string replace(const std::string& in) {
	std::vector<std::string> vector;
	size_t j=0;

	while(j<in.length()) {
		size_t i=j;
		while(i < in.length() && in[i] != ' ') i++;
		vector.push_back(in.substr(j, i-j));
		j = i;

		while(j < in.length() && in[j] == ' ') {
				vector.push_back("%20");
				j++;
			}
	}

	std::stringstream ss;
	for(size_t i=0; i<vector.size(); i++) {
		ss << vector[i];
	}

	return ss.str();
}

int main(int argc, char** argv) {

	std::map<std::string, std::string> testCases;
	testCases["hello my name is Artiom"] = "hello%20my%20name%20is%20Artiom";
	testCases["hello  a "] = "hello%20%20a%20";
	testCases["hello"] = "hello";
	testCases[" h e l l o"] = "%20h%20e%20l%20l%20o";
	testCases["  "] = "%20%20";
	testCases[""] = "";

	for_each(testCases.begin(), testCases.end(), [](const
				std::pair<std::string, std::string>& pair){
			if (pair.second == replace(pair.first)) {
				std::cout << "Passed: ";
			} else {
				std::cout << "Failed: ";
			}
			std::cout << pair.first << " -> " << replace(pair.first) << std::endl;
			});
	return 0;
}
