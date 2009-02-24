#include "..\include\NumberFormats.h"

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