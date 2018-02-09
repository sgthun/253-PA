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

int main(int argc,char* argv[]){
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

}
