#ifndef COLLECTION_INCLUDE
#define COLLECTION_INCLUDE
#include <Collection.h>
#include <Replace.h>
#include<WordCounts.h>
#include <map>

using std::map;
class Collection{
public:
	Collection(int N);
	//~Collection();
	int addDocument(istream& fileName, Replace exceptions);
	bool compareSimilar();
	void printSimilarTbl();
	double sim(WordCounts& docA,  WordCounts& docB);
	double TFIDF(Word& wordIn);
	
protected:
	int NumDocs;
	double Novern;
	int Docs;
	void addToIDF(const WordCounts& words);
	map<string, int> IDF;
	vector<WordCounts> library;
	vector<vector<double>> simularities;
};







#endif
