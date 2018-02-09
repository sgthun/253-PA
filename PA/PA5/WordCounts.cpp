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

// WordCounts::WordCounts(const Replace& exec){
// 	exceptionTable = exec;
// }


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
			//cout<<"stemming: "<<word<<endl;
			//addTmp = word;
			
			//cout<<addTmp<<endl;
			if(stemBox.shouldStem(word)){
				addTmp = exceptionTable.swapString(word);
				if(addTmp.length()<1){
					stemBox.getStem(word);
					stringList.push_back(word);
				}else{
				stringList.push_back(addTmp);
				}
			}else{
				stringList.push_back(word);
			}
			//cout<<"to: "<<word<<endl;	
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
		if(regBox.propCap(stringList.at(index))){
			if (index==0||regBox.puncOnlyEOS(stringList[index-1])){
			stringList.at(index)=("+"+stringList[index]);
			capChecks.push_back(index);
			}else{
				exceptionTable.addCapital(stringList[index]);
				//cout<<stringList[index]<<endl;
				//check if i need index here too
			}
		}
	}
	
}


void WordCounts::checkCaps(){
	for(unsigned int i=0; i<capChecks.size(); ++i){
		capTmp = stringList[capChecks[i]].substr(1, stringList[capChecks[i]].length()-1);
		if(exceptionTable.contains(capTmp)){
			stringList[capChecks[i]] = capTmp;
		}else{
			capTmp = ((char)(capTmp[0]-'A'+'a'))+capTmp.substr(1, capTmp.length()-1);
			if(stemBox.shouldStem(capTmp)){
					
				addTmp = capTmp;
				addTmp = exceptionTable.swapString(addTmp);
				//cout<<addTmp<<" is From Swap"<<endl;
					
				if(addTmp.length()<1){
					stemBox.getStem(capTmp);
					stringList[capChecks[i]] = capTmp;
					
				}else{
					//stemBox.getStem(addTmp);
					stringList[capChecks[i]] = addTmp;
				}
			}else{
				stringList[capChecks[i]] = capTmp;		
			}
		}
	}
}



void WordCounts::removeCapAmb(){
	for(unsigned int index=0;index<stringList.size();index++){

// 		if(stringList[index][0] > '+'){
// 			return;
// 		}
		//regex so i don't split +.!" 
		if(stringList[index][0] == '+'){
			capTmp = stringList[index].substr(1, stringList[index].length()-1);
			if(!exceptionTable.contains(capTmp)){
				capTmp = ((char)(capTmp[0]-'A'+'a'))+capTmp.substr(1, capTmp.length()-1);
				//cout<<capTmp<<" is toLower"<<endl;
				if(stemBox.shouldStem(capTmp)){
					
					addTmp = capTmp;
					addTmp = exceptionTable.swapString(addTmp);
					//cout<<addTmp<<" is From Swap"<<endl;
					
					if(addTmp.length()<1){
						stemBox.getStem(capTmp);
						stringList[index] = capTmp;
					
					}else{
						//stemBox.getStem(addTmp);
						stringList[index] = addTmp;
					}
				}else{
				stringList[index] = capTmp;
				}
			}else{
				stringList[index] = capTmp;
			}
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
		string tmp;//get this to the .h
		
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
		//cout<<(char)wordList[index].getWord()[0]<<" = "<<(int)wordList[index].getWord()[0]<<endl;
	}
}
int WordCounts::stringLength(){
	return stringList.size();
}


