#ifndef WORD_COUNT_INCLUDE
#define WORD_COUNT_INCLUDE
#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<string>
#include<Word.h>
using std::istream;
using std::ostream;
using std::cout;
using std::cin;
using std::endl;
using std::cerr;
using std::vector;

class WordCounts {
public:
	
	int scanFileIn(istream& inFile);
	void sortList();
	void printList();
	void countWords();
	int stringLength();
private:
	
	vector<Word> wordList;
	vector<string> stringList;
};
#endif
