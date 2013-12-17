#include <iostream>
#include <string>
#include <cstring>

int main(int arc, char** argv) {

	std::string s;
	std::cin >> s;
	char* cs = new char[s.length() + 1];
	std::strcpy(cs, s.c_str());

	char* reverse = new char[s.length() + 1];

	for(size_t i=1; i<=std::strlen(cs); i++) {
		*(reverse+i-1) = cs[strlen(cs) - i];
	}

	std::cout << reverse << std::endl;

	return 0;
}
