#include <Stemmer.h>
#include <gtest/gtest.h>


TEST(portAlg, step1){
	Stemmer ss;
	string t = "\'people\'s";
	ss.getStem(t);
	EXPECT_EQ("peopl",t );

}

// TEST(portAlg, step2){
// 	Stem ss;
// 	string t = "abcsses";
// 	ss.step2(t);
// 	EXPECT_EQ("abcss",t);
// }
int main(int argc, char** argv){
	// :: means global scope
	::testing::InitGoogleTest(&argc,argv);
	return RUN_ALL_TESTS();
}
