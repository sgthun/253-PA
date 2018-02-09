#include <Collection.h>
#include <math.h>
#include <iostream>
using std::cout;
using std::endl;

Collection::Collection(int N=0):NumDocs(N){
	//library = new vector<wordCounts>(NumDocs);
	Docs = 0;
}
int Collection::addDocument(istream& fileName, Replace exceptions){
	library.push_back( WordCounts(exceptions));
	library[Docs].scanFileIn(fileName);
	if(library[Docs].stringLength()==0){
		cerr<<"Sneaky empty file"<<endl;
		return -1;
	}
			library[Docs].capitalFix();
			library[Docs].checkCaps();
			library[Docs].sortList();
			library[Docs].countWords();
			//library[Docs].printList();
			
			for(unsigned int wordi = 0; wordi < library[Docs].wordList.size(); ++wordi){
				//check if is AlphaNumeric Here and only do if it is:
				
				
				//FIX STILL
				
				
				//
				if(!library[Docs].regBox.purePuncCheck(library[Docs].wordList.at(wordi).getWord())){
					if(IDF.find(library[Docs].wordList.at(wordi).getWord()) != IDF.end()){
						(IDF[library[Docs].wordList.at(wordi).getWord()])=1+IDF[library[Docs].wordList.at(wordi).getWord()];
						//cout<<"Incrimenting: "<< library[Docs].wordList.at(wordi).getWord()<<endl;
					}else{
						IDF[library[Docs].wordList.at(wordi).getWord()]=1;
						//cout<<"Adding: "<< library[Docs].wordList.at(wordi).getWord()<<endl;
					}
					//cout<<library[Docs].wordList.at(wordi).getWord()<<" has IDF : \n"<<IDF[library[Docs].wordList.at(wordi).getWord()]<<endl;
// 					if(IDF[library[Docs].wordList.at(wordi).getWord()]==0){
// 						cerr<<library[Docs].wordList.at(wordi).getWord()<<" has IDF : \n"<<IDF[library[Docs].wordList.at(wordi).getWord()]<<endl;
// 					}
				}
			}
	++Docs;
	return 0;
}

bool Collection::compareSimilar(){
	//cout<<NumDocs<<endl;
	for(int k=0; k<NumDocs; ++k){
		simularities.push_back(vector<double>(NumDocs));
	}
	for(int i = 0; i<NumDocs;++i){
		//cout<<i<<endl;
		
		for(int j = i; j<NumDocs;++j){
		//	cout<<j<<endl;
			simularities.at(i).at(j) = sim(library.at(i),library.at(j));
			simularities[j][i] = simularities[i][j];
			
		}
	}
	return true;
}

void Collection::printSimilarTbl(){
	//string buffer = "                                   ";
	//char* tmp;
	cout.precision(17);
	for(int i = 0; i<NumDocs;++i){
		for(int j = 0; j<NumDocs;++j){
			cout<<simularities[i][j] << " ";
			//sprintf(tmp,"%f", simularities[j][i]);
			//cout<<(string(tmp)+buffer).substr(0,15);
		}
		cout<<endl;
		//delete [] simularities[i];
	}
}
//Need to make a map <string, int> for TF in WordCounts to speed things up...
//possibly not neccisary if i hand over the TF and iterate parallely all the checking might be more than all the 0*IDF work. testing things througout might be slower than mute math...
double Collection::TFIDF(Word& wordIn){
	Novern = (double)NumDocs/(double)IDF[wordIn.getWord()];
	//cout<<"N = "<<(long double)NumDocs<<"\nn = "<<(long double)IDF[wordIn.getWord()]<<"\nN/n = "<<Novern<<"\nlog10(N/n) = "<<log10(Novern)<<endl;
	//cout<<"N = "<<(long double)NumDocs<<"\nn = "<<(long double)IDF[wordIn.getWord()]<<"\nN/n = "<<Novern<<"\nlog10(N/n) = "<<log10(Novern)<<"\nTFIDF("<<wordIn.getWord()<<") = "<<(wordIn.getCount()*(log10((double)NumDocs/(double)IDF[wordIn.getWord()])))<<"\n"<<endl;
	if(IDF[wordIn.getWord()]==0){
		cout<<wordIn.getWord()<<" = 0"<<endl;
	}
	return (wordIn.getCount()*(log10((double)NumDocs/(double)IDF[wordIn.getWord()])));
}

double Collection::sim( WordCounts& docA, WordCounts& docB){
	//Need to impliment 
	//bool done = false;
	double total = 0;
	int aIndex = 0;
	int bIndex = 0;
	int aMax = docA.wordList.size();
	int bMax = docB.wordList.size();
	string strA;
	string strB;
	int cmp;
	while((aIndex<aMax) && (bIndex<bMax)){
		cmp = docA.wordList.at(aIndex).getWord().compare(docB.wordList.at(bIndex).getWord());
		//cout<<cmp<<" = "<<docA.wordList.at(aIndex).getWord()<<" .compare( "<<docB.wordList.at(bIndex).getWord()<<" )"<<endl;
		//cout<<cmp<<" = cmp"<<endl;
		if(cmp == 0){
			if(!docA.regBox.purePuncCheck(docA.wordList.at(aIndex).getWord())&& !docB.regBox.purePuncCheck(docB.wordList.at(bIndex).getWord())){
			total += (TFIDF(docA.wordList.at(aIndex))*TFIDF(docB.wordList.at(bIndex)));
			}
			aIndex++;
			bIndex++;
			//cout<<total<<" = running Total"<<endl;
// 			if(IDF[docA.wordList.at(aIndex-1).getWord()]==0 || IDF[docB.wordList.at(bIndex-1).getWord()]==0 ){
// 				cout<<"A: "<<IDF[docA.wordList.at(aIndex).getWord()]<<"\nB:"<<IDF[docB.wordList.at(bIndex).getWord()]<<endl;
// 			}
		}else if(cmp >0){
			bIndex++;
			
		}else{
			aIndex++;
			
		}
	}
	return total;
	
}
// Collection::~Collection(){
// 	for(int i = 0 ; i<simularities.size(); i++){
// 		delete &(simularities[i]);
// 	}
// 	
// }








