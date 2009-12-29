#include "../include/NumberFormats.h"
#include <StringConverter.h>
#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>
#include <iostream>

using namespace com::sefh::unitrecognition;

char* NumberFormats::digits[10] = { "","egy","kettő","három","négy","öt","hat","hét","nyolc","kilenc" };
char* NumberFormats::tens[12] = { "","tizen","huszon","harminc","negyven","ötven","hatvan","hetven","nyolvan","kilencven","tíz","húsz" };
char* NumberFormats::hundred = "száz";
char* NumberFormats::thousand = "ezer";
char* NumberFormats::million = "millió";
char* NumberFormats::milliard = "milliárd";
char* NumberFormats::thousandmilliard = "ezermilliárd";

double NumberFormats::writtenNumberToDouble(std::string input)
{

	char* text = new char[150];
	text = strcpy(text,input.c_str());
	char *milliardP, *millionP, *thousandP, *e, *tmpP, *thousandmilliardP;
	char partOfNum[100];
	double returnValue = 0;

	thousandmilliardP = strstr(text, thousandmilliard);
	if(thousandmilliardP != NULL)
	{
		if(thousandmilliardP == text)
			return 1e12;
		else {
			strncpy(partOfNum, text, thousandmilliardP - text);
			tmpP = thousandmilliardP + strlen(thousandmilliard);
			returnValue += 1e12 * partOfNumberValue(partOfNum);
		}
	} else {
		tmpP = text;
	}

	milliardP = strstr(tmpP, milliard);
	if(milliardP != NULL)
	{
		if(milliardP == tmpP || returnValue == 0)
			return 1e9;
		else
		{
			strncpy(partOfNum, tmpP, milliardP - tmpP);
			tmpP = milliardP + strlen(milliard);
			returnValue += 1e9 * partOfNumberValue(partOfNum);
		}
	}

	millionP = strstr(tmpP, million);
	if(millionP != NULL)
	  {
		if(millionP == tmpP || returnValue == 0)
			return 1e6;
		strncpy(partOfNum, tmpP, millionP - tmpP);
		tmpP = millionP + strlen(million);
		returnValue += 1e6 * partOfNumberValue(partOfNum);
	  }

	thousandP = strstr(tmpP, thousand);
	if(thousandP != NULL)
	{
		strncpy(partOfNum, tmpP, thousandP - tmpP);
		tmpP = thousandP + 4;
		int v = partOfNumberValue(partOfNum);
		if(v == 0) v = 1;
		returnValue += 1000 * v ;
	}

	if(*tmpP) returnValue += partOfNumberValue(tmpP);

	free(text);
	return returnValue;
}

int NumberFormats::partOfNumberValue(std::string input)
{
	if(input == "")
		return 1;

	//if the number is not a string
	std::string trimmedInput(input);
	boost::trim(trimmedInput);

	if(isInt(trimmedInput))
	{
		return atoi(trimmedInput.c_str());
	}

	char *hundredP, *tmpP;
	char *text = new char[150];
	text = strcpy(text,input.c_str());
    int j = 0;
    int returnValue;

    hundredP = strstr(text, hundred);
	if(hundredP)
	{
		for(j=1; j<10; j++)
			//if(!strnicmp(digits[j], text, strlen(digits[j])))
			//TODO:: helyettesíteni a fenti sorokat)
			if(true)
            {
				returnValue = 100*j;
                break;
            }

		if(j==10) returnValue = 100;
        tmpP = hundredP+4;
    }
    else
    {
		tmpP = text;
        returnValue = 0;
    }

    for(j=1; j<10; j++)
    {
        if(strstr(tmpP, tens[j]))
        {
			returnValue += 10*j;
            tmpP = tmpP+strlen(tens[j]);
            break;
        }
    }

    if(!strncmp(tens[10], tmpP, 3)) returnValue += 10;
    if(!strncmp(tens[11], tmpP, 4)) returnValue += 20;

    for(j=1; j<10; j++)
    {
		if(strstr(tmpP, digits[j]))
        {
			returnValue += j;
            break;
        }
    }

    free(text);
    return returnValue;
}

NumberFormats::NumberFormats(std::string sep)
{
	createFormatStr(sep);
}

NumberFormats::~NumberFormats(void)
{
}

//TODO:: mi a helyzet a '.'-tal illetve a '\s'-szel?
void NumberFormats::createFormatStr(std::string sep)
{
	if(sep == "")
		formatString = "(-){0,1}\\d+";
	else
		formatString ="(-){0,1}\\d+(["+sep+"]{0,1}\\d)*\\d*";
	formatString ="("+formatString+")|([^\\d\\s]+)|(\\d+\\s(milliárd|millió|ezer))";
}

NumberFormats* NumberFormats::getNumberFormatFromSeparators(std::string sep)
{
	return new NumberFormats(sep);
}

std::string NumberFormats::getRegExpString()
{
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
	unit = boost::regex_replace(unit, boost::regex("[^-\\d"+decimalSep+"]"), "");
	if(unit == "")
	{
		try{
			return writtenNumberToDouble(_unit);
		} catch(...) {
			std::cout<<"Conversation problem with " + _unit;
			return 0;
		}
	}
	unit = boost::regex_replace(unit, boost::regex(decimalSep), ".");



	return atof(unit.c_str());

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
