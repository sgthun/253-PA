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
#include<Stemmer.h>
#include<Replace.h>
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
	
	WordCounts(const Replace& exec):exceptionTable(exec){}
	
	
	int scanFileIn(istream& inFile);
	void sortList();
	void printList();
	void countWords();
	int stringLength();
	//~WordCounts();
	
	
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
	void removeCapAmb();
	void checkCaps();
	//regex alphaNumeric ("[a-zA-Z0-9']+");
	vector<Word> wordList;
	vector<string> stringList;
	vector<int> capChecks;
	int wordCount;
	ParseBox regBox;
	Stemmer stemBox;
	Replace exceptionTable;
	string tmp;
	string addTmp;
	string capTmp;
};
#endif
