#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <algorithm>

bool isSubstring(const std::string& str1, const std::string& str2) {
	return str2.find(str1) != std::string::npos;
}

std::string getRotation(const size_t& start, const std::string& in) {
	if(in == "") return "";
	std::string str = std::string(in.length(), ' ');
	size_t j=0, i=start;
	do
		str[j++] = in[i++ % in.length()];
	while (j < in.length());
	return str;
}

std::string getAllRotations(const std::string& in) {
	std::stringstream sstream;
	for(size_t i=0; i<in.length(); i++) {
		sstream << getRotation(i, in);
	}
	return sstream.str();
}

bool isRotation(const std::string& str1, const std::string& str2) {
	return (str1.length() == str2.length() &&
			isSubstring(str1, getAllRotations(str2)));
}

int main (int argc, char** argv) {
	std::cout.setf(std::ios::boolalpha);
	typedef std::pair<std::string, bool> mpair;
	std::multimap<std::string, mpair> testCases;
	testCases.insert(std::pair<std::string, mpair>
		("worst", mpair("orstw", true)));
	testCases.insert(std::pair<std::string, mpair>
		("worst", mpair("stwor", true)));
	testCases.insert(std::pair<std::string, mpair>
		("worst", mpair("orswt", false)));
	testCases.insert(std::pair<std::string, mpair>
		("", mpair("", true)));

	for_each(testCases.begin(), testCases.end(), [](const
				std::pair<const std::string, mpair>& entry) {
			if(isRotation(entry.first, entry.second.first) ==
				entry.second.second)
				std::cout << "Passed. ";
			else 
				std::cout << "Failed. ";
			std::cout << entry.first << " -> " <<
			entry.second.first << ". " <<
			entry.second.second << std::endl;
		});


	return 0;
}
