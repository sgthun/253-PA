#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include <fstream>
#include <vector>
using std::ifstream;
using std::cerr;
#include<WordCounts.h>
#include<Replace.h>
#include<Collection.h>
using std::istringstream;

int Usage(char* arg0)
{
  cerr << "Usage: " << arg0 <<" exception file1 file2 Low High..." << endl;
  return -1;
}
int fileFail(const char* arg2){
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
			if(corpse.addDocument(fileIstr, exceptions, argv[argi])==-1){
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
	if(wordCount.scanFileIn(fileIstr, argv[1])==0){
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
int getSimReadingLvl(char* argv[]){
	ifstream cmpDocIstr(argv[1]);
	if(cmpDocIstr.fail()){
		return fileFail(argv[1]);
	}
	
	ifstream fileListIstr(argv[2]);
	if(fileListIstr.fail()){
		return fileFail(argv[2]);
	}
	string exceptionFile;
	fileListIstr.peek();
	if(!fileListIstr.eof()==0){
		cerr<<"Empty File List File"<<endl;
		return fileFail(argv[2]);
	}
	fileListIstr>>exceptionFile;
	
	
	
	fileListIstr.peek();
	if(!fileListIstr.eof()==0){
		cerr<<"No files beyond Exception Provided"<<endl;
		return fileFail(argv[2]);
	}
	
	string fileName;
	ifstream* tmpStream;
	vector<ifstream*> streamVec;
	vector<string> fileNames;
	int fileCount = 0;
	while(!fileListIstr.fail()){
		fileListIstr >> fileName;
		if(!fileListIstr.fail()){
			tmpStream = new ifstream(fileName);
			if(tmpStream->fail()){
				//Fail to open a file from the List
				return fileFail(fileName.c_str());
			}
			//Add fileStream to list to create Docs.
			//cout<<fileName<<endl;
			streamVec.push_back(tmpStream);
			fileNames.push_back(fileName);
			fileCount++;
		}
	}
	ifstream exceptionStream = ifstream(exceptionFile);
	Replace exceptions = Replace();
	if(!exceptions.addExceptions(exceptionStream)){
		cerr<<"Exception File Error"<<endl;
		return -1;
	}
	Collection corpse = Collection(fileCount+1);
	if(corpse.addDocument(cmpDocIstr, exceptions, argv[1])==-1){
		cerr<<"Failed with Key Document"<<endl;
		return -1;
	}
	for(int i = 0; i <fileCount; i++){
		//want to add parameter of fileName into WordCounts
		if(corpse.addDocument(*streamVec[i], exceptions, fileNames[i]) == -1){
			cerr<<"Failed Reading a Document"<<endl;
			return -1;
		}
		
	}
	/**
	WordCounts searchDoc(exceptions);
	if(searchDoc.scanFileIn(cmpDocIstr, argv[1]) == -1){
		cerr<<"Search Document had an error"<<endl;
		return -1;
	}
	*/
	
	//Need to call a new function instead of doing compare Similar Here...
	//corpse.compareSimilar();
	//corpse.printSimilarTbl();
	//
	double low;
	double high;
	istringstream lowStream(argv[3]);
	istringstream highStream(argv[4]);
	
	lowStream>>low;
	highStream>>high;
	if(lowStream.fail() != 0 || highStream.fail() != 0 ){
		cerr<<"Invalid Reading Level"<<endl;
		return -1;
	}
	//cout<<lowStream.fail()<<endl;
	
	
	string fileFound = corpse.getSimInRange(low, high);
	if(fileFound.size() == 0){
		cerr<<"No files in range"<<endl;
		return -1;
	}
	cout<<fileFound<<endl;
	return 0;
}

int main(int argc,char* argv[]){
		if(argc != 5){
			return Usage(argv[0]);
		}else{
			return getSimReadingLvl(argv);
		}
		
		

}


