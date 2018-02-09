#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<algorithm>
#include<WordCounts.h>
#include<regex>
using std::regex; // may or may not need
using std::istream;
using std::ostream;
using std::cout;
using std::cin;
using std::endl;
using std::cerr;
using std::string;
using std::exception;



void WordCounts::splitAdd(string& word){
	//cout<<"checking: "<<word<<endl;
	if(regBox.isLegal(word)){
		
		//cout<<"adding: "<<word<<endl;
		add(word);
	}else{
		split(word);
	}
	
}
void WordCounts::add(string word){
	//to gain speed, i may want to resize and work off an index, and as i approach max size, grow vector and use index, then resize to count after everything is in.... push_back is slow like snail
	if(stemBox.shouldStem(word)){
			//cout<<"stemming: "<<word<<endl;
			stemBox.getStem(word);
			//cout<<"to: "<<word<<endl;
		}
	stringList.push_back(word);
	++wordCount;
}
void WordCounts::split(string word){
	string front;
	string back;
	int index = regBox.longestLegalIndex(word);
	//cerr<<"splitting "<<word<<" at index: "<<index<<endl;
	front = word.substr(0,index);
	back = word.substr(index,word.size()-index); 
	//cout<<"adding: "<<front<<endl;
	add(front);
	splitAdd(back);
}

void WordCounts::capitalFix(){
	for(unsigned int index=0;index<stringList.size();index++){
		if(regBox.propCap(stringList.at(index))&& (index==0||regBox.puncOnlyEOS(stringList[index-1]))){
			stringList.at(index)=("+"+stringList[index]);
		}
	}
}
int WordCounts::scanFileIn(istream& inFile){
	wordCount=0; // might move this to constructor later
	inFile.peek();
	if(!inFile.eof()==0){
		cerr<<"Empty file"<<endl;
		return -1;
	}
	while(!inFile.fail()){
		string tmp;
		
		inFile >> tmp;
		
		if(!inFile.fail()){
			splitAdd(tmp);
		}else if(inFile.fail()){
			inFile.clear();
			inFile.peek();
			if(inFile.eof()>0){
				return 0;
			}else{
				cerr<<"Non int in File"<<endl;
				return -1;
			}
		}else{
			cerr<<"Bad Value in File"<<endl;
			return -1;
		}
	}
	return 0;
}
void WordCounts::sortList(){
	sort(stringList.begin(), stringList.end());
	
}
void WordCounts::countWords(){
	// Come back and reszie wordList to wordCount before this step and use and index and ++ rather than push_back() for speed run...
	string curWord;
	string nullStr = string("");
	int wordIndex=0;
	Word tmpWord = Word(stringList[wordIndex]);
	
	wordList.push_back(tmpWord);
	curWord = wordList[wordIndex].getWord();
	int strListSize = stringList.size();
	for(int stringIndex = 1; stringIndex < strListSize; stringIndex++){
		
		while( stringIndex < strListSize && curWord.compare(stringList[stringIndex])==0){
			
			wordList[wordIndex].incrementWord();
			stringIndex++;
		}
		
		if(stringIndex < strListSize){
			wordList.push_back(Word(stringList[stringIndex]));
			wordIndex++;
			curWord = wordList[wordIndex].getWord();
		}else{
			
			break;
		}
		
		
	}
	
}
void WordCounts::printList(){
	//change to wordList after flattening String into Word.
	for(unsigned int index=0;index< wordList.size() ;index++){
		cout<<wordList[index].getWord()<<" "<<wordList[index].getCount()<<endl;
	}
}
int WordCounts::stringLength(){
	return stringList.size();
}


