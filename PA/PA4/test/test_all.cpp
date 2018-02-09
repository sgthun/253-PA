#include <gtest/gtest.h>
#include <Stemmer.h>

TEST(portAlg, step1){
	Stemmer stm;
	string word = "\'cause";
	stm.getStem(word);
	EXPECT_EQ("caus", word);
	word = "ole\'";
	stm.getStem(word);
	EXPECT_EQ("ole", word);
	word = "programmer\'s";
	stm.getStem(word);
	EXPECT_EQ("programm", word);
	
}
TEST(portAlg, step2){
	Stemmer stm;
	string word = "masses";
	stm.getStem(word);
	EXPECT_EQ("mass", word);
}
TEST(portAlg, step3){
	Stemmer stm;
	string word = "goateedly";
	stm.getStem(word);
	EXPECT_EQ("goate", word);
	word = "exceed";
	stm.getStem(word);
	EXPECT_EQ("exce", word);
}
TEST(portAlg, step4){
	Stemmer stm;
	string word = "decry";
	stm.getStem(word);
	EXPECT_EQ("decri", word);
}
TEST(portAlg, step5){
	Stemmer stm;
	string word = "exceptional";
	stm.getStem(word);
	EXPECT_EQ("except", word);
	word = "anxiousness";
	stm.getStem(word);
	EXPECT_EQ("anxious", word);
	word = "irrational";
	stm.getStem(word);
	EXPECT_EQ("irrat", word);
}



int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
