#ifndef WORD_COUNT_INCLUDE
#define WORD_COUNT_INCLUDE
#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<string>
#include<Word.h>
#include<regex>
#include<ParseBox.h>
using std::regex;
using std::istream;
using std::ostream;
using std::cout;
using std::cin;
using std::endl;
using std::cerr;
using std::vector;
using std::string;
class WordCounts {
public:
	
	int scanFileIn(istream& inFile);
	void sortList();
	void printList();
	void countWords();
	int stringLength();
	
	void splitAdd(string& word);
	void add(string word);
	void split(string word);
	bool isAlphanum(string word);
	int getFirstLegalPuncIndex(string word);
	int getFirstLegalAlphIndex(string word);
	bool isAlphaChar(char c);
	bool propCap(string word);
	bool puncOnlyEOS(string word);
	void capitalFix();
private:
	//regex alphaNumeric ("[a-zA-Z0-9']+");
	vector<Word> wordList;
	vector<string> stringList;
	int wordCount;
	ParseBox regBox;
};
#endif