#ifndef NUMBER_SCANNER
#define NUMBER_SCANNER

#include<iostream>
#include<fstream>
using std::istream;
using std::ostream;




class Numscan {
public:
	/**
	Numscan()
	:numbers({}){}
	//*/
	inline void addNumber(int num) {numbers[num]++;}
	inline int getCount(int index) {return numbers[index];}
	
	//inline int * getNumbers(){return &numbers;}
	/**
	int scanFile(istream& sfile);
	int printNums();
	//*/
private:
	int numbers[20];
	
};


#endif
