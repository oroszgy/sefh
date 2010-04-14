#include "../include/NumberFormats.h"
#include <StringConverter.h>
#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>
#include <iostream>
#include "constants.h"

#define DIGITSLENGTH 10
#define TENSLENGTH 12

using namespace com::sefh::unitrecognition;

char* NumberFormats::half = "fél";
char* NumberFormats::digits[DIGITSLENGTH] = { "","egy","kettő","három","négy","öt","hat","hét","nyolc","kilenc" };
char* NumberFormats::tens[TENSLENGTH] = { "","tizen","huszon","harminc","negyven","ötven","hatvan","hetven","nyolvan","kilencven","tíz","húsz" };
char* NumberFormats::hundred = "száz";
char* NumberFormats::thousand = "ezer";
char* NumberFormats::million = "millió";
char* NumberFormats::milliard = "milliárd";
char* NumberFormats::billion= "billió";
char* NumberFormats::thousandmilliard = "ezermilliárd";

double writtenNumberToDouble(std::string input);

bool NumberFormats::isEqual(std::string inp1, std::string inp2) {
	return inp1 == inp2;
}

//P:hasString
std::string NumberFormats::getStrBefore(std::string input, std::string splitter) {
	size_t sPos = input.find(splitter);
	if (sPos != std::string::npos)
		return input.substr(0, sPos);
	else
		return "";
}

//P: hasString
std::string NumberFormats::getStrAfter(std::string input, std::string splitter) {
	size_t sPos = input.find(splitter);
	if (sPos != std::string::npos)
		return input.substr(sPos + splitter.length());
	else
		return input;
}

//P: not null
bool NumberFormats::hasStr(std::string input, std::string str) {
	return (input.find(str) != std::string::npos);
}

//P:hasString
double NumberFormats::convertDigits(std::string input) {
	if(isEqual(std::string(half), input))
			return 0.5;
	if(isEqual(std::string(digits[DIGITSLENGTH-1]), input))
			return 2;
	for(int i=0; i<DIGITSLENGTH-1; ++i) {
		if(isEqual(std::string(digits[i]), input))
			return i;
	}

	return -1;
}

//P:hasString
double NumberFormats::convertTens(std::string input) {
	for(int i=1; i<TENSLENGTH-2; ++i) {
		if(hasStr(input, std::string(tens[i])))
		{
			return i*10 + convertDigits(getStrAfter(input, std::string(tens[i])));
		}
	}
	for(int i=1; i<3; ++i) {
			if(hasStr(input, std::string(tens[i+TENSLENGTH-3])))
			{
				return i*10;
			}
	}
	return convertDigits(input);
}

//P:hasString
double NumberFormats::convertHundreds(std::string input) {
	if(!hasStr(input, hundred))
		return convertTens(input);

	std::string before, after;
	before = getStrBefore(input, hundred);
	after = getStrAfter(input, hundred);
	double beforeVal, afterVal;
	beforeVal = convertDigits(before);
	afterVal = convertTens(after);
	if(afterVal == -1 || beforeVal == -1)
		return -1;

	if(beforeVal == 0)
		beforeVal = 1;
	return beforeVal * 100 + afterVal;
}

//P:hasString
double NumberFormats::convertThousands(std::string input) {
	if(!hasStr(input, thousand))
		return convertHundreds(input);
	std::string before, after;
	before = getStrBefore(input, thousand);
	after = getStrAfter(input, thousand);
	double beforeVal, afterVal;
	beforeVal = convertHundreds(before);
	afterVal = convertHundreds(after);
	if(afterVal == -1 || beforeVal == -1)
		return -1;

	if(beforeVal == 0)
		beforeVal = 1;
	return beforeVal * 1000 + afterVal;

}

double NumberFormats::convertMillion(std::string input) {
	if(!hasStr(input, million))
			return convertThousands(input);
		std::string before, after;
		before = getStrBefore(input, million);
		after = getStrAfter(input, million);
		double beforeVal, afterVal;
		beforeVal = convertThousands(before);
		afterVal = convertThousands(after);
		if(afterVal == -1 || beforeVal == -1)
			return -1;

		if(beforeVal == 0)
			beforeVal = 1;
		return beforeVal * 1000 * 1000 + afterVal;


}

double NumberFormats::convertMilliard(std::string input) {
	if(!hasStr(input, milliard))
			return convertMillion(input);
	std::string before, after;
	before = getStrBefore(input, milliard);
	after = getStrAfter(input, milliard);
	double beforeVal, afterVal;
	beforeVal = convertThousands(before);
	afterVal = convertThousands(after);
	if(afterVal == -1 || beforeVal == -1)
		return -1;

	if(beforeVal == 0)
		beforeVal = 1;
	return beforeVal * 1000 * 1000 * 1000 + afterVal;
}

double NumberFormats::convertBillion(std::string input) {
	if(!hasStr(input, billion))
			return convertMilliard(input);
	std::string before, after;
	before = getStrBefore(input, billion);
	after = getStrAfter(input, billion);
	double beforeVal, afterVal;
	beforeVal = convertThousands(before);
	afterVal = convertThousands(after);
	if(afterVal == -1 || beforeVal == -1)
		return -1;

	if(beforeVal == 0)
		beforeVal = 1;
	return beforeVal * 1000 * 1000 * 1000 * 1000 + afterVal;
}

//positive, written in a single word, without any other character and spaces, not null
double NumberFormats::writtenNumberToDouble(std::string input) {
	return convertBillion(input);
}

NumberFormats::NumberFormats(std::string sep)
{
	createFormatStr(sep);
}

NumberFormats::~NumberFormats(void)
{
}

//TODO:: mi a helyzet a '.'-tal illetve a '\s'-szel?
void NumberFormats::createFormatStr(std::string s)
{
	std::string sep = std::string(SEP);

	std::string ws = sep;//"(\\\\s)";
	//std::string whitespaces = "("+whitespace+"+)";
	std::string digit = "(\\\d)";
	std::string digits = "("+digit+"+)";
	std::string dws = "("+digits+ws+")";
	std::string number = "("+dws+"*"+dws+"(,"+ws+dws+"){0,1}"+")";
	std::string numberSuffix = "("+std::string(thousand)+"|"+std::string(million)+"|"+std::string(milliard)+"|"+std::string(billion)+")";
	std::string numberValue = "("+number+numberSuffix+"{0,1})";
	std::string textValue = buildTextValueStr();
	std::string value = "("+textValue+"|"+numberValue+")";
	formatString = value;
	/*
	if(sep == "")
		formatString = "(-){0,1}\\d+";
	else
		formatString ="(-){0,1}\\d+(["+sep+"]{0,1}\\d)*\\d*";
	formatString ="("+formatString+")|([^\\d\\s]+)|(\\d+\\s(milliárd|millió|ezer))";*/
}

std::string NumberFormats::buildTextValueStr() {
	std::string txtNum = /*std::string(ADDSTR) +*/ "((";
	for(int i=1; i<DIGITSLENGTH; ++i) {
		txtNum += std::string(digits[i]) + "|";
	}

	txtNum += std::string(half) + "|";

	for(int i=1; i<TENSLENGTH; ++i) {
		txtNum += std::string(tens[i]) + "|";
	}

	txtNum += std::string(hundred) + "|";
	txtNum += std::string(thousand) + "|";
	txtNum += std::string(million) + "|";
	txtNum += std::string(milliard) + "|";
	txtNum += std::string(billion);

	txtNum += std::string(")+") /*+ ADDSTR*/ + ")";

	return "(("+txtNum+"-)*"+txtNum +")";
}

NumberFormats* NumberFormats::getNumberFormatFromSeparators(std::string sep)
{
	return new NumberFormats(sep);
}

std::string NumberFormats::getRegExpString()
{
	//Debug
	//std::cout<<formatString<<std::endl;
	return formatString;
}

double NumberFormats::convertToDouble(std::string decimalSep, std::string _unit)
{
	std::string unit(_unit);

	/*std::string::iterator it = unit.begin();
	while(it!=unit.end())
	{
		if(!isInt(*it) && *it != boost::)
			unit.erase(it);
		++it;
	}*/

	//contains not deciaml character?
	bool hasNotDecimal = boost::regex_search(unit, boost::regex("[^\\\s\\\d"+decimalSep+"]"));
	bool hasDecimal = boost::regex_search(unit, boost::regex("[\\\d]"));

	std::cout<<std::endl<<unit<<hasNotDecimal<<hasDecimal<<std::endl;
	std::string unitDec = boost::regex_replace(unit, boost::regex("[^\\\d"+decimalSep+"]"), "");
	unitDec = boost::regex_replace(unitDec, boost::regex(decimalSep), ".");
	std::string unitAlpha = boost::regex_replace(unit, boost::regex("[-\\\s\\\d"+decimalSep+"]"), "");
	if(hasDecimal && !hasNotDecimal)
	{
		double numval = atof(unitDec.c_str());
		return numval;
	}
	else if (hasNotDecimal && !hasDecimal)
	{
		try{
			double res = writtenNumberToDouble(unitAlpha);
			if( res > 0)
				return res;
			else
				return 0;
		} catch(...) {
			std::cout<<"Conversation problem with " + _unit;
			return 0;
		}
	} else if (hasNotDecimal && hasDecimal) {
		double numVal = atof(unitDec.c_str());
		double alphaVal = writtenNumberToDouble(unitAlpha);
		return numVal * alphaVal;
	}

	return 0;

}

bool NumberFormats::isInt(char c)
{
	int ci = atoi(&c);
	char* cic = new char[10];
	cic	= itoa(ci, cic, 10);
	return cic[0] == c;
}

bool NumberFormats::isInt(std::string& str) {
	for(size_t i=0; i<str.length(); ++i) {
		if(!isInt(str[i]))
			return false;
	}
	return true;
}
