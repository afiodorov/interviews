#include <iostream>
#include <algorithm>
#include <map>

int main(int argc, char** argv) {
	std::map<char,int> mStr;
	std::string s;
	std::cin >> s;

	for_each(s.begin(), s.end(), [&mStr](std::string::const_reference c)
			{mStr[c]++;});

	bool isUnique = std::accumulate(mStr.begin(), mStr.end(), true, 
			[](const bool &a, const std::pair<const char, int> &b){
			return a && (b.second == 1);});

	if (isUnique) std::cout << "All characters are unique" << std::endl;
	else std::cout << "Not all characters are unique" << std::endl;

	return 0;
}
