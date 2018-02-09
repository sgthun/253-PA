#include<Stemmer.h>
#include<iostream>
using std::string;
using std::cout;
using std::endl;

Stemmer::Stemmer(){
	needsStem = regex("[a-z']{3,}");
	rOneReg = regex("(.*?)('s'|'s|')");
	containsVowel = regex("(.*[aeiou].*|.*[^aeiou]y.*|^yy.*)");
	//regionOne = regex("((.*?[aeiou]|.*?[^aeiou]y|^yy)[^aeiou]{1})(.*)");
	regionOneC1 = regex("(.*?[aeiou][^aeiou]{1})(.*)");
	regionOneC2 = regex("(.*?[^aeiou]y[^aeiou]{1})(.*)");
	regionOneC3 = regex("(^yy[^aeiou]{1})(.*)");
	endShort = regex("(.*)([^aeiouy]|(([aeiou]|^|yy)+)y)[aeiouy][^aeiouywx]");
	twoVC = regex("[aeiou][^aeiou]");
	fourLong2 = regex("(.*)(sses)");
	threeLong2 = regex("(.*)(ied|ies)");
	twoLong2 = regex("(.*)(us|ss)");
	oneLong2=regex("(.*)(s)");
	eedOeedly = regex("(.*)(eed|eedly)");
	rule3bundle = regex("(.*)(ed|edly|ing|ingly)");
	endsWatOblOiz = regex("(.*)(at|bl|iz)");
	endsDouble = regex("(.*)(bb|dd|ff|gg|mm|nn|pp|rr|tt)");
	endsNonVowel = regex("(.*)([^aeiouy]|(([aeiou]|^|yy)+)y)");
	sevenLong5 = regex("(.*)(ization|ational|fulness|ousness|iveness)");
	ization = regex("(.*)(ization)");
	ational = regex("(.*)(ational)");
	fulness = regex("(.*)(fulness)");
	ousness = regex("(.*)(ousness)");
	iveness = regex("(.*)(iveness)");
	sixLong5 = regex("(.*)(tional|biliti|lessli)");
	tional = regex("(.*)(tional)");
	biliti = regex("(.*)(biliti)");
	lessli = regex("(.*)(lessli)");
	fiveLong5 = regex("(.*)(entli|ation|alism|aliti|ousli|iviti|fulli)");
	entli = regex("(.*)(entli)");
	ation = regex("(.*)(ation)");
	alismOaliti = regex("(.*)(alism|aliti)");
	ousli = regex("(.*)(ousli)");
	iviti = regex("(.*)(iviti)");
	fulli = regex("(.*)(fulli)");
	fourLong5 = regex("(.*)(enci|anci|abli|izer|ator|alli)");
	enci = regex("(.*)(enci)");
	anci = regex("(.*)(anci)");
	izer = regex("(.*)(izer)");
	ator = regex("(.*)(ator)");
	alli = regex("(.*)(alli)");
	threeLong5 = regex("(.*)(bli|ogi)");
	bli = regex("(.*)(bli)");
	ogi = regex("(.*)(ogi)");
	endsWl = regex("(.*)(l)");
	li = regex("(.*)(li)");
	validli = regex("(.*)(c|d|e|g|h|k|m|n|r|t)");
	regionOneGroupRule6 = regex("(.*)(ational|tional|alize|icate|icite|iciti|ical|ful|ness)");
	//ational = regex("(.*)(ational)");
	//tional = regex("(.*)(tional)");
	alize = regex("(.*)(alize)");
	icateOiciti = regex("(.*)(icate|iciti)");
	ical = regex("(.*)(ical)");
	nessOful = regex("(.*)(ness|ful)");
	ative = regex("(.*)(ative)");
	ement = regex("(.*)(ement)");
	ment = regex("(.*)(ment)");
	stepSevenBundle = regex("(.*)(al|ance|ence|er|ic|able|ible|ant|ent|ism|ate|iti|ous|ive|ize)");
	ion = regex("(.*)(ion)");
	endWsOt = regex("(.*)(s|t)");
	e =regex("(.*)(e)");
	l = regex("(.*)(l)");
	
	
	
	
	
	
	
	
	
	
	
}
string Stemmer::region1(const string& word){
	smatch region1Match;
	//regex regionOne = regex("((.*?[aeiou]|.*?[^aeiou]y|^yy)[^aeiou]{1})(.*)");
	//regex_match(word, region1Match, regionOne);
	//regex regionOneC1 = regex("(.*?[aeiou][^aeiou]{1})(.*)");
	//regex regionOneC2 = regex("(.*?[^aeiou]y[^aeiou]{1})(.*)");
	//regex regionOneC3 = regex("(^yy[^aeiou]{1})(.*)");
	unsigned int shortest = 0;
	string regionOne = string("");
	if(regex_match(word, region1Match, regionOneC1)){
		shortest = string(region1Match[1]).length();
		regionOne = region1Match[2];
	}
	
	if(regex_match(word, region1Match, regionOneC2)){
		if(string(region1Match[1]).length()<shortest || shortest==0){
			shortest = string(region1Match[1]).length();
			regionOne= region1Match[2];
		}
	}
	if(regex_match(word, region1Match, regionOneC3)){
		if(string(region1Match[1]).length()<shortest|| shortest==0){
			shortest = string(region1Match[1]).length();
			regionOne= region1Match[2];
		}
	}
	
	return regionOne;
	
}
bool Stemmer::endsInShort(const string& word){
	//regex endShort = regex("(.*)([^aeiouy]|(([aeiou]|^|yy)+)y)[aeiouy][^aeiouywx]");
	//regex twoVC = regex("[aeiou][^aeiou]");
	return regex_match(word, twoVC) || regex_match(word, endShort);
}
bool Stemmer::isShort(const string& word){
	return endsInShort(word) && (string(region1(word)).size() == 0);
}
bool Stemmer::shouldStem(const string& word){
	return regex_match(word,needsStem);
}
void Stemmer::getStem(string& word){
	rule1(word);
	rule2(word);
	rule3(word);
	rule4(word);
	rule5(word);
	rule6(word);
	rule7(word);
	rule8(word);
}
bool Stemmer::rule1(string& word){
	//check Investigate if removing ' at begining counts as completing the alg...
	//regex rOneReg = regex("(.*?)('s'|'s|')");
		if(word.at(0) == '\''){
			//cout<<word<<endl;
			word = word.substr(1,word.length()-1);
		}
		
		if(regex_match(word,strMatch,rOneReg)){
			word = word.substr(0,strMatch.length(1));
			return true;
		}
		return false;
}
bool Stemmer::rule2(string& word){
	//regex fourLong2 = regex("(.*)(sses)");
	if(regex_match(word,strMatch,fourLong2)){
		word = word.substr(0,strMatch.length(1)) + string("ss");
		return true;
	}
	//regex threeLong2 = regex("(.*)(ied|ies)");
	if(regex_match(word,strMatch,threeLong2)){
		word = word.substr(0,strMatch.length(1))+string((strMatch.length(1)>1)?string("i"):string("ie"));
		return true;
	}
	//regex twoLong2 = regex("(.*)(us|ss)");
	if(regex_match(word,strMatch,twoLong2)){
		return true;//blocking the s from being dropped.
	}
	//regex oneLong2=regex("(.*)(s)");
	if(regex_match(word,strMatch,oneLong2)){
		string preceder1less = string(strMatch[1]).substr(0,string(strMatch[1]).size()-1);
		if(regex_match(preceder1less,containsVowel)){
			//if ends in an S and contains a vowel, here we are...
			//cout<<"does containVowel"<<endl;
			//regex preceederEndsCons = regex("(.*[^aeiouy])|(.*(((^|[aeiou])(yy)*)y))");
			//if(regex_match(string(strMatch[1]),preceederEndsCons)){
				//cout<<"peceeder ends in cons"<<endl;
				word = string(strMatch[1]);
				return true;
			//}
			
		}
	}
	
	
		return false;
}
bool Stemmer::rule3(string& word){
	//regex eedOeedly = regex("(.*)(eed|eedly)");
	string tempRegion= region1(word);
	if(regex_match(word,eedOeedly)){
		if(regex_match(tempRegion, strMatch, eedOeedly)){
			regex_match(word, strMatch, eedOeedly);
			word = string(strMatch[1])+string("ee");
			return true;
		}
		return false;
	}
	// Need to handle ed|edly|ing|ingly still.
	//regex rule3bundle = regex("(.*)(ed|edly|ing|ingly)");
	if(regex_match(word, strMatch, rule3bundle)){
		//cout<<"(ed|edly|ing|ingly)"<<endl;
		if(regex_match(string(strMatch[1]),containsVowel)){
			//regex endsWatOblOiz = regex("(.*)(at|bl|iz)");
			if(regex_match(string(strMatch[1]),endsWatOblOiz)){
				word = string(strMatch[1])+string("e");
				return true;
			}
			//regex endsDouble = regex("(.*)(bb|dd|ff|gg|mm|nn|pp|rr|tt)");
			if(regex_match(string(strMatch[1]),endsDouble)){
				word = string(strMatch[1]).substr(0,string(strMatch[1]).size()-1);
				//check that -1 is right and we don't need -2
				return true;
			}
			string preceederTmp = string(strMatch[1]);
			if(isShort(preceederTmp)){
				word = string(strMatch[1])+string("e");
				return true;
			}
			word = string(strMatch[1]);
		}	
	}
	
		return false;
}
bool Stemmer::rule4(string& word){
	regex y = regex("(.*)y");
	if(regex_match(word, strMatch, y)){
		//regex endsNonVowel = regex("(.*)([^aeiouy]|(([aeiou]|^|yy)+)y)");
		string preceedTmp = string(strMatch[1]);
		if(regex_match(preceedTmp,endsNonVowel) && (preceedTmp.size()>1)){
			word = string(strMatch[1])+string("i");
			
		}
	}
		return false;
}
bool Stemmer::rule5(string& word){
	//regex sevenLong5 = regex("(.*)(ization|ational|fulness|ousness|iveness)");
	if(regex_match(word, strMatch, sevenLong5)){
		//regex ization = regex("(.*)(ization)");
		if(regex_match(word, strMatch, ization)){
			word = string(strMatch[1])+string("ize");
			return true;
		}
		//regex ational = regex("(.*)(ational)");
		if(regex_match(word, strMatch, ational)){
			word = string(strMatch[1])+string("ate");
			return true;
		}
		//regex fulness = regex("(.*)(fulness)");
		if(regex_match(word, strMatch, fulness)){
			word = string(strMatch[1])+string("ful");
			return true;
		}
		//regex ousness = regex("(.*)(ousness)");
		if(regex_match(word, strMatch, ousness)){
			word = string(strMatch[1])+string("ous");
			return true;
		}
		//regex iveness = regex("(.*)(iveness)");
		if(regex_match(word, strMatch, iveness)){
			word = string(strMatch[1])+string("ive");
			return true;
		}
	}
	//regex sixLong5 = regex("(.*)(tional|biliti|lessli)");
	if(regex_match(word, sixLong5)){
		//regex tional = regex("(.*)(tional)");
		if(regex_match(word, strMatch, tional)){
			word = string(strMatch[1])+string("tion");
			return true;
		}
		//regex biliti = regex("(.*)(biliti)");
		if(regex_match(word, strMatch, biliti)){
			word = string(strMatch[1])+string("ble");
			return true;
		}
		//regex lessli = regex("(.*)(lessli)");
		if(regex_match(word, strMatch, lessli)){
			word = string(strMatch[1])+string("less");
			return true;
		}
	}
	//regex fiveLong5 = regex("(.*)(entli|ation|alism|aliti|ousli|iviti|fulli)");
	if(regex_match(word, strMatch, fiveLong5)){
		//regex entli = regex("(.*)(entli)");
		if(regex_match(word, strMatch, entli)){
			word = string(strMatch[1])+string("ent");
			return true;
		}
		//regex ation = regex("(.*)(ation)");
		if(regex_match(word, strMatch, ation)){
			word = string(strMatch[1])+string("ate");
			return true;
		}
		//regex alismOaliti = regex("(.*)(alism|aliti)");
		if(regex_match(word, strMatch, alismOaliti)){
			word = string(strMatch[1])+string("al");
			return true;
		}
		//regex ousli = regex("(.*)(ousli)");
		if(regex_match(word, strMatch, ousli)){
			word = string(strMatch[1])+string("ous");
			return true;
		}
		//regex iviti = regex("(.*)(iviti)");
		if(regex_match(word, strMatch, iviti)){
			word = string(strMatch[1])+string("ive");
			return true;
		}
		//regex fulli = regex("(.*)(fulli)");
		if(regex_match(word, strMatch, fulli)){
			word = string(strMatch[1])+string("ful");
			return true;
		}
	}
	//regex fourLong5 = regex("(.*)(enci|anci|abli|izer|ator|alli)");
	if(regex_match(word, strMatch, fourLong5)){
		//regex enci = regex("(.*)(enci)");
		if(regex_match(word, strMatch, enci)){
			word = string(strMatch[1])+string("ence");
			return true;
		}
		//regex anci = regex("(.*)(anci)");
		if(regex_match(word, strMatch, anci)){
			word = string(strMatch[1])+string("ance");
			return true;
		}
		//regex izer = regex("(.*)(izer)");
		if(regex_match(word, strMatch, izer)){
			word = string(strMatch[1])+string("ize");
			return true;
		}
		//regex ator = regex("(.*)(ator)");
		if(regex_match(word, strMatch, ator)){
			word = string(strMatch[1])+string("ate");
			return true;
		}
		//regex alli = regex("(.*)(alli)");
		if(regex_match(word, strMatch, alli)){
			word = string(strMatch[1])+string("al");
			return true;
		}
	}
	//regex threeLong5 = regex("(.*)(bli|ogi)");
	if(regex_match(word, strMatch, threeLong5)){
		//regex bli = regex("(.*)(bli)");
		if(regex_match(word, strMatch, bli)){
			word = string(strMatch[1])+string("ble");
			return true;
		}
		//regex ogi = regex("(.*)(ogi)");
		if(regex_match(word, strMatch, ogi)){
			//regex endsWl = regex("(.*)(l)");
			if(regex_match(string(strMatch[1]),endsWl)){
				word = string(strMatch[1])+string("og");
				return true;
			}
		}
		
	}
	//regex li = regex("(.*)(li)");
	if(regex_match(word, strMatch, li)){
		//regex validli = regex("(.*)(c|d|e|g|h|k|m|n|r|t)");
		if(regex_match(string(strMatch[1]),validli)){
			word = string(strMatch[1]);
			return true;
		}
	}
		return false;
}
bool Stemmer::rule6(string& word){
	//regex regionOneGroupRule6 = regex("(.*)(ational|tional|alize|icate|icite|iciti|ical|ful|ness)");
	string regionTemp = region1(word);
	if(regex_match(regionTemp,strMatch, regionOneGroupRule6)){
		//regex ational = regex("(.*)(ational)");
		if(regex_match(word, strMatch, ational)){
			word = string(strMatch[1])+string("ate");
			return true;
		}
		//regex tional = regex("(.*)(tional)");
		if(regex_match(word, strMatch, tional)){
			word = string(strMatch[1])+string("tion");
			return true;
		}
		//regex alize = regex("(.*)(alize)");
		if(regex_match(word, strMatch, alize)){
			word = string(strMatch[1])+string("al");
			return true;
		}
		//regex icateOiciti = regex("(.*)(icate|iciti)");
		if(regex_match(word, strMatch, icateOiciti)){
			word = string(strMatch[1])+string("ic");
			return true;
		}
		//regex ical = regex("(.*)(ical)");
		if(regex_match(word, strMatch, ical)){
			word = string(strMatch[1])+string("ic");
			return true;
		}
		//regex nessOful = regex("(.*)(ness|ful)");
		if(regex_match(word, strMatch, nessOful)){
			word = string(strMatch[1]);
			return true;
		}
	}
	//regex ative = regex("(.*)(ative)");
	regionTemp = region1(region1(word));
	if(regex_match(regionTemp, strMatch, ative)){
		regex_match(word, strMatch, ative);
		word = string(strMatch[1]);
		return true;
	}
		return false;
}
bool Stemmer::rule7(string& word){
	//regex ement = regex("(.*)(ement)");
	string tempRegion= region1(region1(word));
	
	//cout<<word<<" has region1: "<<region1(word)<<" has region 2: "<<tempRegion<<endl;
	if(regex_match(word, strMatch, ement)){
		if(regex_match(tempRegion, strMatch, ement)){
			regex_match(word, strMatch, ement);
			word = string(strMatch[1]);
			return true;
		}
		return false;
	}
	//regex ment = regex("(.*)(ment)");
	if(regex_match(word, strMatch, ment)){
		if(regex_match(tempRegion, strMatch, ment)){
			regex_match(word, strMatch, ment);
			word = string(strMatch[1]);
			return true;
		}
		return false;
	}
	//regex stepSevenBundle = regex("(.*)(al|ance|ence|er|ic|able|ible|ant|ent|ism|ate|iti|ous|ive|ize)");
	if(regex_match(tempRegion, strMatch, stepSevenBundle)){
		regex_match(word, strMatch, stepSevenBundle);
		word = string(strMatch[1]);
		return true;
	}
	//regex ion = regex("(.*)(ion)");
	if(regex_match(tempRegion, strMatch, ion)){
		regex_match(word, strMatch, ion);
		//regex endWsOt = regex("(.*)(s|t)");
		if(regex_match(string(strMatch[1]),endWsOt)){
			word = string(strMatch[1]);
			return true;
		}
	}
		return false;
}
bool Stemmer::rule8(string& word){
	//regex e = regex("(.*)(e)");
	if(regex_match(word, strMatch, e)){
		string temp8 = region1(word);
		if((!endsInShort(string(strMatch[1]))) && regex_match(temp8,e)){
			word = string(strMatch[1]);
			return true;
		}
		temp8 = region1(region1(word));
		if(regex_match(temp8, e)){
			word = string(strMatch[1]);
			return true;
		}
		return false;
	}
	//regex l = regex("(.*)(l)");
	if(regex_match(word, strMatch, l)){
		string temp8 = region1(region1(word));
		if(regex_match(temp8, l)){
			temp8 = string(strMatch[1]);
			if(regex_match(temp8, l)){
				word = string(strMatch[1]);
				return true;
			}
		}
	}
		return false;
}
