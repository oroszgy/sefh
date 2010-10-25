#include "../include/HunSynonym.h"
#include "HumorCPP.h"
#include <string>
#include <iostream>
#include "path.h"

using namespace com::sefh::hunstemmer;

HunSynonym* com::sefh::hunstemmer::HunSynonym::instance = NULL;

HunSynonym::HunSynonym() {
	com::weblib::linguist::HumorCPP::initialize(LEX);
}

HunSynonym::~HunSynonym() {
	com::weblib::linguist::HumorCPP::close();
}

HunSynonym* HunSynonym::getInstance() {
	if(instance == NULL)
		instance = new HunSynonym();

	return instance;

}

std::string HunSynonym::processQuery(std::string& query) {

	try
	{
		if(query == "")
			return query;

		std::string myquery(query);
		std::string marker = "~";
		std::string sepChars = " .,;:-(){}[]\n\t\r";
		int mPos, wsPos;
		std::string buf, word, rem;

		//split the word till ~
		while((mPos = myquery.find_first_of("~"))!= std::string::npos) {
			buf = myquery.substr(0,mPos);
			myquery = myquery.substr(mPos + 1, myquery.length() - mPos -1);
			//find the first whitespace
			wsPos = myquery.find_first_of(sepChars);
			if(wsPos == std::string::npos)
			{
				word = myquery;
				rem = "";
			}
			else
			{
				word = myquery.substr(0,wsPos);
				rem = myquery.substr(wsPos, myquery.length() - wsPos);
			}
			myquery = buf + generateSynString(word) + rem;

		}

		return myquery;
	}
	catch(...)
	{
		return query;
	}
}

std::string HunSynonym::generateSynString(std::string& wordM) {
	std::string word(wordM);
	std::string pre, post, wrapLeft, wrapRight;
	pre = "#syn("; post=")";
	wrapLeft = "#1("; wrapRight = ")";

	std::string ret = ""; ret += pre;

	std::vector<std::string> syns = com::weblib::linguist::HumorCPP::getSyns(word);
	if(syns.size() == 0)
		return word;

	for(int i=0; i< syns.size(); ++i) {
		ret += wrapLeft;
		ret += syns[i];
		ret += wrapRight;
	}
	ret += post;
	return ret;
}

std::vector<std::string> HunSynonym::getSyns(std::string& word) {
	return com::weblib::linguist::HumorCPP::getSyns(word);
}



