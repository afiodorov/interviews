#include <iostream>
#include <string>
#include <map>
#include <algorithm>

std::string deleteDuplicates(const std::string& in) {
	std::string s(in);
	for(size_t i=0; i<s.length()-1; i++) {
		for(size_t j=i+1; j<s.length();j++) {
			if(s[i] == s[j]) s.erase(j--,1);
		}
	}
	return s;
}

int main() {
	std::map<std::string, std::string> tests;
	tests["hhh"] = "h";
	tests["lamo"] = "lamo";
	tests["dupplicates"] = "duplicates";
	tests["rrnroxox"] = "rnox";

	int counter = 0;
	bool hasPassedAll = std::accumulate(tests.begin(), tests.end(), true,
			[&counter](const bool &a, const std::pair<const std::string, std::string> &p){
				bool hasPassed = (p.second == deleteDuplicates(p.first));
				if(hasPassed) {
					std::cout << "Passed " << p.second << " -> " << p.first << std::endl;
				} else {
					std::cout << "Failed " << p.second 
						<< " -> " << p.first << std::endl;
					counter++;
				}
				return hasPassed && a;
			});

	std::cout << std::string(20, '-') << std::endl;
	if(hasPassedAll) std::cout << "All Passed!" << std::endl;
	else std::cout << "Have failed: " << counter << std::endl;

	return 0;
}
