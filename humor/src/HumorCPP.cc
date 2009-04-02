#include "../include/HumorCPP.h"
#include <stdlib.h>
#include <iostream>

using namespace com::weblib::linguist;

void HumorCPP::initialize(std::string dir, int langCode)
{
	using namespace java::lang;
	JvCreateJavaVM(NULL);
	JvAttachCurrentThread(NULL, NULL);
	JvInitClass(&System::class$);
	Humor::initialize(convertToJavaStr(&dir), 1038);
}

bool HumorCPP::isInitialized()
{
	return Humor::isInitialized();
}

int HumorCPP::close()
{
    int sum = 0;
    sum += Humor::closeStemming();
    sum += 2*Humor::closeWordGenerating();
    sum += 4*Humor::closeWordFormsGenerating();
	JvDetachCurrentThread();

	return sum;
}

std::vector<std::string>* HumorCPP::getStem(std::string word)
{
	jstring jword = convertToJavaStr(&word);
	return javaStrArraytoVector(Humor::getStem(jword));
}

std::vector<std::string>* HumorCPP::getAnalyze(std::string word)
{
        jstring jword = convertToJavaStr(&word);
        return javaStrArraytoVector(Humor::getAnalyze(jword));
}

std::vector<std::string>* HumorCPP::getWordGenerate(std::string word)
{
        jstring jword = convertToJavaStr(&word);
        return javaStrArraytoVector(Humor::getWordGenerate(jword));
}

std::vector<std::string>* HumorCPP::getWordForms(std::string word, int limit)
{
        jstring jword = convertToJavaStr(&word);
        return javaStrArraytoVector(Humor::getWordForms(jword, limit));
}

std::vector<std::string>* HumorCPP::getSyns(std::string word, int contextSize)
{
          jstring jword = convertToJavaStr(&word);
          return javaStrArraytoVector(Humor::getWordForms(jword, contextSize));
}

void HumorCPP::TestError(std::string word, int limit)
{
        jstring jword = convertToJavaStr(&word);
        Humor::TestError(jword, limit);
}

std::string* HumorCPP::getStrFromJava(java::lang::String* jStr)
{
	char* buf;
	int bufLength = JvGetStringUTFLength(jStr);
	int length = jStr->length();
	buf = new char[bufLength + 1];
	JvGetStringUTFRegion (jStr, 0, length, buf);
	buf[bufLength] = '\0';

	return new std::string(buf);
}

java::lang::String* HumorCPP::convertToJavaStr(std::string* str)
{
	std::string tmpStr = *str;
	return JvNewStringUTF(tmpStr.c_str());
}

std::vector<std::string>* HumorCPP::javaStrArraytoVector(JArray<java::lang::String* >* array)
{
	if(array != NULL)
	{
		jstring * tmpArray = elements(array);
		std::vector<std::string>* ret = new std::vector<std::string>();
		std::string* tmpStr = NULL;
		for(jsize i=0; i<array->length; ++i)
		{
			tmpStr =  getStrFromJava(tmpArray[i]);
			ret->push_back(*tmpStr);
		}

		return ret;
	}
	else
	{
		return NULL;
	}
}



