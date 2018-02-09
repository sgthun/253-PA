#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include <fstream>
using std::ifstream;
using std::cerr;
#include<WordCounts.h>
#include<Replace.h>
#include<Collection.h>


int Usage(char* arg0)
{
  cerr << "Usage: " << arg0 <<" exception file1 file2..." << endl;
  return -1;
}
int fileFail(char* arg2){
	cerr<<"Failed to open file: "<<arg2<<endl;
	return -1;
}
int exceptionFail(char* arg1){
	cerr<<"Failed to open exception: "<<arg1<<endl;
	return -1;
}
int runCollection(int argc, char* argv[]){
	if (argc < 4) return Usage(argv[0]);
		ifstream execIstr(argv[1]);
		if(execIstr.fail())return exceptionFail(argv[1]);
		
		
		Replace exceptions = Replace();
		if(!exceptions.addExceptions(execIstr)){
			return -1;
		}
		Collection corpse = Collection(argc-2);
		ifstream fileIstr;
		for(int argi = 2; argi<argc; ++argi){
			fileIstr = ifstream(argv[argi]);
			if (fileIstr.fail()){
				return fileFail(argv[argi]);
			}
			if(corpse.addDocument(fileIstr, exceptions)==-1){
				cerr<<"Failed reading the document "<<argv[argi]<<endl;
				return -1;
			}
		}
		corpse.compareSimilar();
		//<<"about to print"<<endl;
		corpse.printSimilarTbl();
		return 0;
}
int runReadScore(int argc,char* argv[]){
	Replace exceptions = Replace();
	ifstream fileIstr(argv[1]);
	if (fileIstr.fail()) return fileFail(argv[1]);
	WordCounts wordCount = WordCounts(exceptions);
	if(wordCount.scanFileIn(fileIstr)==0){
		if(wordCount.stringLength()==0){
			cerr<<"Sneaky empty file"<<endl;
			return -1;
		}else if(wordCount.wordCounter == 0){
			cerr<<"No words in File"<<endl;
			return -1;
		}
		wordCount.capitalFix();
		//wordCount.sortList();
		//wordCount.removeCapAmb();
		wordCount.checkCaps();
		wordCount.sortList();
		wordCount.countWords();
		//wordCount.printList();
		//cout<<wordCount.L()<<endl<<wordCount.S()<<endl<<wordCount.wordCounter<<endl;
		cout<<wordCount.CLindex()<<endl;
		return 0;
	}else{
		cerr<<"Error Scanning File"<<endl;
		return -1;
	}
	
	return 0;
}
int main(int argc,char* argv[]){
		switch(argc){
			case 2:{
				return runReadScore(argc, argv);
			}
			case 3:{
				// could expand to cover case here
				return Usage(argv[0]);
			}
			default:{
				return Usage(argv[0]);//comment out this line when Done with PA7
				return runCollection(argc, argv);
			}
		}

}
