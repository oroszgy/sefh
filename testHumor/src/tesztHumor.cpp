#include "HumorCPP.h"
#include <iostream>
#include <stdlib.h>
#include "DateFormat.h"

#include <vector>


int main(int args, char** argv)
{
	using namespace com::weblib::linguist;
	//HumorCPP * h = new HumorCPP();
	//HumorCPP::initialize("/home/mee/Projects/testHumor",1038);

/*
	std::string testInput = "öüóőúéáűí";
	const char* testInpuChararray = testInput.c_str();

	jstring latin,utf;
	latin = JvNewStringLatin1(testInpuChararray);
	utf = JvNewStringUTF(testInpuChararray);

	char* bufLatin = new char[JvGetStringUTFLength(latin)];
	JvGetStringUTFRegion(latin,0,JvGetStringUTFLength(latin), bufLatin);

	char* bufUtf = new char[JvGetStringUTFLength(utf)];
	JvGetStringUTFRegion(utf,0,JvGetStringUTFLength(utf), bufUtf);
	java::lang::System::out->println(latin);
	java::lang::System::out->println(utf);

	std::cout<<"eredeti:\t"+testInput;
	std::cout<<"latin:\t"<<bufLatin;
	std::cout<<"utf:\t"<<utf;
*/


	/*std::vector<std::string>* stems = HumorCPP::getStem("kutyákat");
	if(stems != NULL)
		std::cout<<stems->at(0);
	else
		std::cout<<"null?\n";

	std::string s("árvíztűrő");
	stems = HumorCPP::getStem(s);
		if(stems != NULL)
			std::cout<<stems->at(0);
		else
			std::cout<<"null?\n";

	HumorCPP::close();*/

	using namespace com::sefh::daterecognising;
	std::vector<DateFormat> dateVec = DateFormat::getInstances()[0];
	DateFormat f = dateVec[0];
	std::string date = "2008. május 1.";
	std::string day = f.getDay(date);
	std::string month = f.getMonth(date);
	std::string year = f.getYear(date);
	std::string m = f.getMonthIntegerString(date);

	//bool b = com::sefh::utils::StringConverter::isPrefix("máj", "május");

	return 0;
}
