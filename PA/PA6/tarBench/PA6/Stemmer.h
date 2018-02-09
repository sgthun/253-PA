#ifndef STEMMER_INCLUDE
#define STEMMER_INCLUDE
#include<regex>
#include<string>
using std::regex;
using std::string;
using std::smatch;

class Stemmer{
public:
	Stemmer();
	bool shouldStem(const string& word);
	void getStem(string& word);
	
private:
	bool rule1(string& word);
	bool rule2(string& word);
	bool rule3(string& word);
	bool rule4(string& word);
	bool rule5(string& word);
	bool rule6(string& word);
	bool rule7(string& word);
	bool rule8(string& word);
	string region1(const string& word);
	bool endsInShort(const string& word);
	bool isShort(const string& word);
	string region2(const string& word);
	
	regex needsStem;
	regex rOneReg;
	smatch strMatch;
	regex containsVowel;
	//regex regionOne;
	regex regionOneC1;
	regex regionOneC2;
	regex regionOneC3;
	regex regionTwoC1;
	regex regionTwoC2;
	regex regionTwoC3;
	regex endShort;
	regex twoVC;
	regex fourLong2;
	regex threeLong2;
	regex twoLong2;
	regex oneLong2;
	regex eedOeedly;
	regex rule3bundle;
	regex endsWatOblOiz;
	regex endsDouble;
	regex endsNonVowel;
	regex sevenLong5;
	regex ization;
	regex ational;
	regex fulness;
	regex ousness;
	regex iveness;
	regex sixLong5;
	regex tional;
	regex biliti;
	regex lessli;
	regex fiveLong5;
	regex entli;
	regex ation;
	regex alismOaliti;
	regex ousli;
	regex iviti;
	regex fulli;
	regex fourLong5;
	regex enci;
	regex anci;
	regex izer;
	regex ator;
	regex alli;
	regex threeLong5;
	regex bli;
	regex ogi;
	regex endsWl;
	regex li;
	regex validli;
	regex regionOneGroupRule6;
	//regex ational;
	//regex tional;
	regex alize;
	regex icateOiciti;
	regex ical;
	regex nessOful;
	regex ative;
	regex ement;
	regex ment;
	regex stepSevenBundle;
	regex ion;
	regex endWsOt;
	regex e;
	regex l;
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
};

#endif
