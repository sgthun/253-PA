#include<string>
using std::string;

class Word{
public:
	Word(string wordIn=""):word(wordIn), count(1){}
	
	inline string getWord()const{return word;}
	inline int getCount(){return count;}
	inline void incrementWord(){count +=1;}
	inline void setWord(string newWord){word = newWord;}
	
	
private:
	string word;
	int count;
};