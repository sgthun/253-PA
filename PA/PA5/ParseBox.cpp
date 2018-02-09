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
	
	commaDecNumber =regex("([0-9]*[\\.]{0,1}[0-9]+)*(([0-9]*[\\.]{0,1}[0-9]+)+([\\.,]{0,1}[0-9]+)*|([a-zA-Z0-9']*[0-9]+[\\.,]{0,1}[0-9]+)*)*[a-zA-Z'0-9]*");
		
	purePunc= regex("^[^a-zA-Z0-9']+");
	//these for splitting
	alphaNumericDS =regex ("(^[a-zA-Z0-9']+)(.*)");
	
	commaDecNumberDS =regex ("(([0-9]*[\\.]{0,1}[0-9]+)*(([0-9]*[\\.]{0,1}[0-9]+)+([\\.,]{0,1}[0-9]+)*|([a-zA-Z0-9']*[0-9]+[\\.,]{0,1}[0-9]+)*)*[a-zA-Z'0-9]*)(.*)");
		
	
	
	purePuncDS= regex("(^[^a-zA-Z0-9']+)(.*)");
	puncDecNumLazy = regex("(^[^a-zA-Z0-9']+)(\\.[0-9]+.*)");
	//these for checking capitalization and punctuation
	startCapOnlyCap =regex("[A-Z]{1}[a-z']*"); 
	puncOnlyEos =regex ("[^a-zA-Z0-9']*[\\.!\\?]+[^a-zA-Z0-9']*");
	numDotFirst = regex("[\\.]{1}[0-9]+(([a-zA-Z'0-9]*[0-9]+)*([\\.,][0-9]+)*)*[a-zA-Z'0-9]*");
		
	numDotFirstDS = regex("([\\.]{1}[0-9]+(([a-zA-Z'0-9]*[0-9]+)*([\\.,][0-9]+)*)*[a-zA-Z'0-9]*)(.*)");
		
	numWithPunc = regex("(([a-zA-Z'0-9]*[0-9]+)+([\\.,][0-9]+)*)*[a-zA-Z'0-9]*");
		
	numWithPuncDS = regex("((([a-zA-Z'0-9]*[0-9]+)+([\\.,][0-9]+)*)*[a-zA-Z'0-9]*)(.*)");
	
}
bool ParseBox::isLegal(const string& word){
	//cout<<word<<endl;
	return (regex_match(word,alphaNumeric)
		|| regex_match(word,purePunc)
		|| regex_match(word,numDotFirst)
		|| regex_match(word,numWithPunc)
	);
	
}
int ParseBox::longestLegalIndex(const string& word){
	indexEOM = 0;
	//special case of puncthuation followed by .num
	/**/
	//cout<<word<<endl;
	if(regex_match(word,legalMatch,puncDecNumLazy)){
		//return legalMatch.length(1);
		indexEOM = legalMatch.length(1);
		//cout<<"puncDecNumLazy\n"<<legalMatch.length(1)<<endl;
	}
	/**/
	regex_match(word, legalMatch, alphaNumericDS);
	if(legalMatch.length(1) > indexEOM){
		indexEOM = legalMatch.length(1);
		//cout<<"alphaNumericDS\n"<<legalMatch.length(1)<<endl;
	}
	regex_match(word, legalMatch, purePuncDS);
	if( legalMatch.length(1) > indexEOM){
		indexEOM = legalMatch.length(1);
		//cout<<"commaDecNumberDS\n"<<legalMatch.length(1)<<endl;
	}
	
	regex_match(word, legalMatch, numDotFirstDS);
	if(legalMatch.length(1) > indexEOM){
		indexEOM = legalMatch.length(1);
		//cout<<"purePuncDS\n"<<legalMatch.length(1)<<endl;
	}
	regex_match(word, legalMatch, numWithPuncDS);
	if( legalMatch.length(1) > indexEOM){
		indexEOM = legalMatch.length(1);
		//cout<<"commaDecNumberDS\n"<<legalMatch.length(1)<<endl;
	}
	//cout<<indexEOM<<"\n"<<endl;
	return indexEOM;
}
bool ParseBox::propCap(const string& word){
	return regex_match(word, startCapOnlyCap);
}
bool ParseBox::puncOnlyEOS(const string& word){
	return regex_match(word, puncOnlyEos);
	
}
