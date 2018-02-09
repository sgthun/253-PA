#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include <fstream>
using std::ifstream;
using std::cerr;
#include <Numscan.h>

int Usage(char* arg0)
{
  cerr << "Usage: " << arg0 << " filename" << endl;
  return -1;
}
//core functionality is working, just need to refine error handling (react accordingly to bad input) and comb over a few corner cases (test tabs and newlines)

int scanIn(ifstream& inFile, Numscan& ns){
	inFile.peek();
	if(!inFile.eof()==0){
		cerr<<"Empty file"<<endl;
		return -1;
	}
	while(!inFile.fail()){
		int tmp;
		inFile >> tmp;
		if(!inFile.fail() && tmp>=0 && tmp<20){
			//break;
			//cout<< tmp<<endl;
			ns.addNumber(tmp);
			//cout<<ns.getCount(tmp)<<endl;
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
		//ns.addNumber(tmp);
	}

	return 0;
}

int printNums(Numscan ns){
	for(int i=0; i<20;i++){
		cout<<i<<" "<<ns.getCount(i)<<endl;
	}
	return 0;
	
}


int main(int argc,char* argv[]){
	
	if (argc != 2) return Usage(argv[0]);
	ifstream istr(argv[1]);
	if (istr.fail()) return Usage(argv[0]);
	
	
	Numscan ns= Numscan();
	if(scanIn(istr, ns)==0){
		return printNums(ns);
	}else{
		return Usage(argv[1]);
	}
	
};
