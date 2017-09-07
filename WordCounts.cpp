#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<algorithm>
#include<WordCounts.h>
using std::istream;
using std::ostream;
using std::cout;
using std::cin;
using std::endl;
using std::cerr;
using std::string;



int WordCounts::scanFileIn(istream& inFile){
	inFile.peek();
	if(!inFile.eof()==0){
		cerr<<"Empty file"<<endl;
		return -1;
	}
	while(!inFile.fail()){
		string tmp;
		cout<<tmp<<endl;
		inFile >> tmp;
		if(!inFile.fail()){
			//need to add Word Here
			//cout<<tmp<<endl;
			stringList.push_back(tmp);
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
	string curWord;
	int wordIndex=0;
	Word tmpWord = Word(stringList[wordIndex]);
	wordList.push_back(tmpWord);
	curWord = wordList[wordIndex].getWord();
	for(unsigned int stringIndex = 1; stringIndex < stringList.size(); stringIndex++){
		
		while(curWord.compare(stringList[stringIndex])==0){
			
			wordList[wordIndex].incrementWord();
			stringIndex++;
		}
		wordList.push_back(stringList[stringIndex]);
		wordIndex++;
		curWord = wordList[wordIndex].getWord();
	}
}
void WordCounts::printList(){
	//change to wordList after flattening String into Word.
	for(unsigned int index=0;index< wordList.size() ;index++){
		cout<<wordList[index].getWord()<<" : "<<wordList[index].getCount()<<endl;
	}
}


