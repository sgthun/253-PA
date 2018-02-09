#include <Replace.h>
//check How gracefully or not this  part fails still.
bool Replace::addExceptions(istream& inExc){
	inExc.peek();
	if(!inExc.eof()==0){
		//cerr<<"Empty exceptions file"<<endl;
		return true;
	}
	legalLine = regex("([a-zA-Z']+)\\s([a-zA-Z']+)\\s*(\n)?");
	int max = 514;// fix this hard coding, risky gamble
	char input[max];
	bool matched = false;
	string temporaryFix;
	while(!inExc.fail()){
		inExc.getline(input,max);
		temporaryFix = string(input);
		matched = regex_match(temporaryFix, excMatch, legalLine);
		if(!matched && temporaryFix.length()>0){
			cerr<<temporaryFix<<"\nWas found in the replacemnt file "<<temporaryFix.length()<<endl;
			return false;
		}
		if(!inExc.fail()){
			//inExc >> tmpScanVal;
			if(!inExc.fail() && matched){
				addKeyVal(string(excMatch[1]) ,string(excMatch[2]) );
			}else if(inExc.fail()){
			inExc.clear();
			inExc.peek();
				if(inExc.eof()>0){
					return true;
				}else{
					cerr<<"Non string in Exceptions"<<endl;
					return false;
				}
			}
		}
	}
	return true;
}

void Replace::addKeyVal(string key, string val){
	wordMap[key]=val;
	//cout<<key<<" maped to "<<wordMap[key]<<endl;
}

string Replace::swapString(const string& in){
	return wordMap[in];
// 	tempString = wordMap[in];
// 	if(tempString.length()>0){
// 		return tempString;
// 	}else{
// 		return in;
// 	}
}
bool Replace::contains(const string& cap){
	auto search = capitalsKnown.find(cap);
	if(search != capitalsKnown.end()){
		return true;
	}
	return false;
}
void Replace::addCapital(const string& cap){
	capitalsKnown.insert(cap);
}
