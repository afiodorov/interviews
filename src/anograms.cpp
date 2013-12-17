#include <iostream>
#include <string>
#include <map>
#include <algorithm>

std::string merge(const std::string& str0, const std::string& str1) {
	std::string result(str0.length() + str1.length(), ' ');
	size_t i0=0, i1=0;
	for(size_t j=0; j<str0.length()+str1.length(); j++) {
		if(i0 < str0.length() && (i1 == str1.length() || str0[i0] < str1[i1]))
			result[j] = str0[i0++];
		else
			result[j] = str1[i1++];
	}
	return result;
}

std::string mergesort(const std::string& str) {
	if(str.length() <= 1) return str;
	else {
		size_t middle = str.length() / 2;
		return merge(mergesort(str.substr(0, middle)),
				mergesort(str.substr(middle)));
	}
};

bool areAnograms(const std::string& str1, const std::string& str2) {
	return (str1.length() == str2.length()) 
		&& (mergesort(str1) == mergesort(str2));
}

int main(int argc, char** argv) {
	std::map<std::string, std::pair<std::string, bool> > testCases;
	testCases["sldfdf"] = std::pair<std::string, bool>("wier", false);
	testCases["test"] = std::pair<std::string, bool>("wier", false);
	testCases["lol"] = std::pair<std::string, bool>("oll", true);
	testCases["h"] = std::pair<std::string, bool>("m", false);
	testCases["hello"] = std::pair<std::string, bool>("olehl", true);
	testCases[""] = std::pair<std::string, bool>("", true);
	testCases["dorothy"] = std::pair<std::string, bool>("dorothw", false);

	std::string isAn[2] = {" (not anagram)", " (anagram)"};
	
	for_each(testCases.begin(), testCases.end(), [&isAn](const
				std::pair<std::string, std::pair<std::string,
				bool>>& pair) {
			if(areAnograms(pair.first, pair.second.first) == pair.second.second)
					std::cout << "Passed test: ";
				else
					std::cout << "Hasn't passed test: ";
				std::cout << pair.first << "->" << pair.second.first 
					<< isAn[pair.second.second] << std::endl;
			});


	return 0;
}
