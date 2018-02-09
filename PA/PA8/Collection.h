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
	int addDocument(istream& fileName, Replace exceptions, string file);
	bool compareSimilar();
	void printSimilarTbl();
	double sim(WordCounts& docA,  WordCounts& docB);
	double TFIDF(Word& wordIn);
	string getSimRdLvlDoc(WordCounts& keyDoc, double lowScore, double highScore);
	string getSimInRange(double low, double high);
	
protected:
	int NumDocs;
	double Novern;
	int Docs;
	void addToIDF(const WordCounts& words);
	map<string, int> IDF;
	vector<WordCounts> library;
	vector<WordCounts> toCompare;
	vector<vector<double>> simularities;
	//vector<double> searchSimular;
};







#endif
