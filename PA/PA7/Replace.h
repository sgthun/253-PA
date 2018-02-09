#ifndef REPLACE_INCLUDE
#define REPLACE_INCLUDE
#include <iostream>
#include <fstream>
using std::string;
using std::istream;
#include <map>
#include <set>
#include <regex>
using std::regex;
using std::smatch;
using std::map;
using std::make_pair;
using std::cerr;
using std::endl;
using std::cout;
using std::set;
class Replace{
public:
	//Replace();
	bool addExceptions(istream& inExc);
	string swapString(const string& in);
	void addCapital(const string& cap);
	bool contains(const string& cap);
private:
	void addKeyVal(string key, string val);
	map<string, string> wordMap;
	
	//Need to move capitalsKnown to wordCounts so that i can pass Replace as a reference to each wordCounts.
	set<string> capitalsKnown;
	
	regex legalLine;
	smatch excMatch;
	string tempString;
	string tmpScanKey;
	string tmpScanVal;
};

#endif
