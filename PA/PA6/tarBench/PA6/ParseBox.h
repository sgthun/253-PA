#ifndef PARSE_BOX_INCLUDE
#define PARSE_BOX_INCLUDE
#include<regex>
#include<string>
#include<stdio.h>
#include<iostream>
using std::regex;
using std::string;
using std::smatch;



class ParseBox {
public:
	ParseBox();
	bool isLegal(const string& word);
	int longestLegalIndex(const string& word);
	bool propCap(const string& word);
	bool puncOnlyEOS(const string& word);
	bool isAlphaNum(const string& word);
	bool purePuncCheck(const string& word);
	
private:	
	/*
	regex alphaNumeric ("[a-zA-Z0-9']+");
	//regex decimalNumber ("[0-9]*\\.[0-9]+"); // Now handled in CommaDecNumber
	regex commaDecNumber ("(([0-9]+[\\.,]{1}[0-9]+)+([\\.,]{1}[0-9]+)*)|(([0-9]*[\\.]{1}[0-9]+)+([\\.,]{1}[0-9]+)*)");
	regex purePunc("[^a-zA-Z0-9']+");
	*/
	regex alphaNumeric;
	regex commaDecNumber;
	regex purePunc;
	regex alphaNumericDS;
	regex commaDecNumberDS;
	regex purePuncDS;
	regex puncDecNumLazy;
	smatch legalMatch;
	int indexEOM;
	regex startCapOnlyCap;
	regex numDotFirst;
	regex numDotFirstDS;
	regex numWithPunc;
	regex numWithPuncDS;
	
	
	regex puncOnlyEos;
	
};



#endif
