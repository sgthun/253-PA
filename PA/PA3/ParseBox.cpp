#include<ParseBox.h>
#include<regex>
#include<string>
#include<stdio.h>
#include<iostream>
using std::regex;
using std::string;
using std::smatch;
using std::cerr;
using std::cout;
using std::endl;

ParseBox::ParseBox(){
	//these for checking legality
	alphaNumeric =regex ("^[a-zA-Z0-9']+");
	commaDecNumber =regex ("^(([0-9]+[\\.,]{1}[0-9]+)+([\\.,]{1}[0-9]+)*)|(([0-9]*[\\.]{1}[0-9]+)+([\\.,]{1}[0-9]+)*)");
	purePunc= regex("^[^a-zA-Z0-9']+");
	//these for splitting
	alphaNumericDS =regex ("(^[a-zA-Z0-9']+)(.*)");
	commaDecNumberDS =regex ("(^(([0-9]+[\\.,]{1}[0-9]+)+([\\.,]{1}[0-9]+)*)|(([0-9]*[\\.]{1}[0-9]+)+([\\.,]{1}[0-9]+)*))(.*)");
	purePuncDS= regex("(^[^a-zA-Z0-9']+)(.*)");
	puncDecNumLazy = regex("(^[^a-zA-Z0-9']+?)(\\.[0-9]+.*)");
	//these for checking capitalization and punctuation
	startCapOnlyCap =regex("[A-Z]{1}[a-z]*");
	puncOnlyEos =regex ("[^a-zA-Z0-9']*[\\.!\\?]+[^a-zA-Z0-9']*");
}
bool ParseBox::isLegal(const string& word){
	
	return (regex_match(word,alphaNumeric) 
	|| regex_match(word,commaDecNumber)
	|| regex_match(word,purePunc));
	
}
int ParseBox::longestLegalIndex(const string& word){
	indexEOM = 0;
	//special case of puncthuation followed by .num
	if(regex_match(word,legalMatch,puncDecNumLazy)){
		return legalMatch.length(1);
	}
	regex_match(word, legalMatch, alphaNumericDS);
	if(legalMatch.length(1) > indexEOM){
		indexEOM = legalMatch.length(1);
	}
	regex_match(word, legalMatch, commaDecNumberDS);
	if( legalMatch.length(1) > indexEOM){
		indexEOM = legalMatch.length(1);
	}
	regex_match(word, legalMatch, purePuncDS);
	if(legalMatch.length(1) > indexEOM){
		indexEOM = legalMatch.length(1);
	}
	return indexEOM;
}
bool ParseBox::propCap(const string& word){
	return regex_match(word, startCapOnlyCap);
}
bool ParseBox::puncOnlyEOS(const string& word){
	return regex_match(word, puncOnlyEos);
	
}
