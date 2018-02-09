#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include <fstream>
using std::ifstream;
using std::cerr;
#include<WordCounts.h>
#include<Replace.h>


int Usage(char* arg0)
{
  cerr << "Usage: " << arg0 <<" exception "<< " filename" << endl;
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

int main(int argc,char* argv[]){
		if (argc != 3) return Usage(argv[0]);
		ifstream fileIstr(argv[2]);
		if (fileIstr.fail()) return fileFail(argv[2]);
		ifstream execIstr(argv[1]);
		if(execIstr.fail())return exceptionFail(argv[1]);
		
		
		Replace exceptions = Replace();
		if(!exceptions.addExceptions(execIstr)){
			return -1;
		}
		
		WordCounts wordCount = WordCounts(exceptions);
		if(wordCount.scanFileIn(fileIstr)==0){
			if(wordCount.stringLength()==0){
				cerr<<"Sneaky empty file"<<endl;
				return -1;
			}
			wordCount.capitalFix();
			//wordCount.sortList();
			//wordCount.removeCapAmb();
			wordCount.checkCaps();
			wordCount.sortList();
			wordCount.countWords();
			wordCount.printList();
			return 0;
		}else{
			cerr<<"Error Scanning File"<<endl;
			return -1;
		}
}
