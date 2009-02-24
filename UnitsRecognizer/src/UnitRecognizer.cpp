#include "..\include\UnitRecognizer.h"

UnitRecognizer::UnitRecognizer(ConfigFileReader* reader)
{
	units = reader->getUnits();
	separators = reader->getSeparators();
	decSep = reader->getDecimalSeparator();
}

UnitRecognizer::~UnitRecognizer()
{
}

std::string UnitRecognizer::getRecognizingRegExp()
{
	std::string unitConstants;
	for(int i=0; i<units->size(); ++i)
	{
		unitConstants+=units->at(i).constant;
		if(i<units->size()-1)
			unitConstants+="|";
	}
	return getRecognizingRegExpFromConstants(unitConstants);
}

//TODO:: lekezelni azt az esetet amikor nincs semmi
std::string UnitRecognizer::getRecognizingRegExpFromConstants(std::string unitConstants)
{
	std::string sep;
	for(int i=0; i<separators->size(); ++i)
	{
		sep += separators->at(i);
	}
	sep += decSep;

	NumberFormats* nf = NumberFormats::getNumberFormatFromSeparators(sep);
	std::string REStr = "(" + nf->getRegExpString() + ")";
	REStr += "\\s*(";
	
	REStr += unitConstants;

	REStr += ')';
	//REStr += "$";
	return REStr;
}

std::map<std::string, std::string>* UnitRecognizer::getUnitsRecognizingRegexps()
{
	std::map<std::string, std::string>* map = new std::map<std::string, std::string>();
	std::vector<Unit>::iterator vecIt;
	for(vecIt = units->begin(); vecIt != units->end(); ++vecIt)
	{
		(*map)[(*vecIt).type] += "|" + (*vecIt).constant;
	}

	std::map<std::string, std::string>::iterator mapIt;
	for(mapIt = map->begin(); mapIt != map->end(); ++mapIt)
	{
		mapIt->second = getRecognizingRegExpFromConstants(mapIt->second.substr(1));
	}

	return map;
}

double UnitRecognizer::getSIValue(std::string unit)
{
	for(int i=0; i<units->size(); ++i)
	{
		std::string re = getRecognizingRegExpFromConstants(units->at(i).constant);
		if(boost::regex_match(unit.begin(), unit.end(), boost::regex(re)))
		{
			boost::regex re(getRecognizingRegExp());
			std::string value = boost::regex_replace(unit, re, "$1");
	
			return NumberFormats::convertToDouble(decSep, value) * units->at(i).multiplier;
		}
	}

	return 0;
}

std::string UnitRecognizer::getTypeOfMeasure(std::string unit)
{
	for(int i=0; i<units->size(); ++i)
	{
		if(unit.find(units->at(i).constant) != std::string::npos)
			return units->at(i).type;
	}
		
	return "";
}
