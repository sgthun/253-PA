#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include <fstream>
using std::ifstream;
using std::cerr;
#include<WordCounts.h>


int Usage(char* arg0)
{
  cerr << "Usage: " << arg0 << " filename" << endl;
  return -1;
}

int main(int argc,char* argv[]){
		if (argc != 2) return Usage(argv[0]);
		ifstream istr(argv[1]);
		if (istr.fail()) return Usage(argv[0]);
		
		WordCounts wordCount = WordCounts();
		if(wordCount.scanFileIn(istr)==0){
			if(wordCount.stringLength()==0){
				cerr<<"Sneaky empty file"<<endl;
				return -1;
			}
			wordCount.sortList();
			wordCount.countWords();
			wordCount.printList();
			return 0;
		}else{
			cerr<<"Error Scanning File"<<endl;
			return -1;
		}
}
