#include <iostream>
#include <fstream>
#include <set>
#include <map>
#include <vector>
#include <memory>
#include <sstream>

typedef std::vector<std::string>::size_type size_type;
typedef std::map<std::string, std::set<size_type>> wordMap;

class QueryResult {
	public:
	QueryResult(const std::string& inword, const std::shared_ptr<wordMap>& inmap,
			const std::shared_ptr<std::vector<std::string>>& infile) : 
		word(inword), map(inmap), file(infile) { processQuery(); }

	std::ostream& show(std::ostream& out) const {
		out << result.str();
		return out;
	}

	QueryResult(const QueryResult& rhs) : result(rhs.result.str()),
		word(rhs.word), map(rhs.map), file(rhs.file) {};

	private:
	std::stringstream result;
	std::string word;
	std::shared_ptr<wordMap> map;
	std::shared_ptr<std::vector<std::string>> file;

	void processQuery() {
		for(size_type lineNumber : (*map)[word]) {
			result << lineNumber << ": " << (*file)[lineNumber]
				<< std::endl;
		}
	};
};

std::ostream& operator<<(std::ostream& out, const QueryResult& qr) { 
	return qr.show(out);
}

class TextQuery {
	public:
	TextQuery(std::ifstream& infile) : file(new std::vector<std::string>()),
	map(new wordMap()) {
		std::string line;
		while(getline(infile, line)) 
			file->push_back(line);
		buildMap();
	}

	QueryResult query(std::string word) {
		return QueryResult(word, map, file);
	}

	private:
	std::shared_ptr<std::vector<std::string>> file;
	std::shared_ptr<wordMap> map;

	void buildMap() {
		for(auto it = file->begin(); it != file->end(); it++) {
			std::stringstream ss(*it);
			std::string item;
			while(std::getline(ss, item, ' ')) {
				size_type lineNumber = it - file->begin();
				(*map)[item].insert(lineNumber);
			}
		}
	}
};

void runQueries(std::ifstream &infile) {
	TextQuery tq(infile);
	std::string s;
	do {
		std::cout << "enter word to look for, or q to quit: " <<
			std::endl;
		std::cout << tq.query(s) << std::endl;
	} while ((std::cin >> s) && s != "q");
}

int main(int argc, char** argv) {
	std::ifstream infile("/home/tom/test.md");
	runQueries(infile);
	infile.close();
	return 0;	
}
