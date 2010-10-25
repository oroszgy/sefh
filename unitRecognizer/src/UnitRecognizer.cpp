#include "../include/UnitRecognizer.h"
#include <boost/regex.hpp>
#include "../include/NumberFormats.h"
#include "Configuration.h"
#include "constants.h"
#include "StringConverter.h"

using namespace com::sefh::unitrecognition;

UnitRecognizer* UnitRecognizer::defaultInstance = NULL;

UnitRecognizer* UnitRecognizer::getDefault()
{
	if(defaultInstance == NULL)
		defaultInstance = new UnitRecognizer();

	return defaultInstance;
}

UnitRecognizer::UnitRecognizer()
{
	com::sefh::utils::Configuration* conf =
		com::sefh::utils::Configuration::getDefault();
	units = conf->getUnits();
	separators = conf->getSeparators();
	decSep = conf->getDecimalSeparator();
}

UnitRecognizer::~UnitRecognizer()
{
	if(units != NULL)
		delete units;
	if(separators != NULL)
		delete separators;
}

std::string UnitRecognizer::getRecognizingRegExp()
{
	//std::cout<<ADDSTR<<std::endl;
	std::string unitConstants;
	for(int i=0; i<units->size(); ++i)
	{
		unitConstants+=units->at(i).constant;
		if(i<units->size()-1)
			unitConstants+= /*std::string(ADDSTR) +*/ "|" /*+ std::string(SUFFIX)*/;
	}

	//DEBUG:
	//std::cout<<std::endl<<"1 :"+unitConstants<<std::endl;

	return getRecognizingRegExpFromConstants(unitConstants);
}

//TODO:: lekezelni azt az esetet amikor nincs semmi
std::string UnitRecognizer::getRecognizingRegExpFromConstants(std::string unitConstants)
{
	std::string sep;
	for(size_t i=0; i<separators->size(); ++i)
	{
		sep += separators->at(i);
	}
	sep += decSep;

	NumberFormats* nf = NumberFormats::getNumberFormatFromSeparators(sep);

	std::string REStr = "(";
	REStr += std::string(PREFIX) + nf->getRegExpString();
	//Debug
	//std::cout<<std::endl<<"-1: " + REStr<<std::endl<<std::endl;
	//std::cout<<std::endl<<"-1.1: " + unitConstants<<std::endl<<std::endl;
	//std::cout<<std::endl<<"-1.1: " + std::string(SUFFIX)<<std::endl<<std::endl;
	REStr += std::string(SEP);
	REStr += "("+unitConstants+std::string(ADDSTR)+")";

	REStr += ')' + std::string(SUFFIX);
	//REStr += "$";
	//Debug
	//std::cout<<std::endl<<"0: " + REStr<<std::endl<<std::endl;
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


	//Debug:
	//std::cout<<"1:\n";
	std::map<std::string, std::string>::iterator mapIt;
	for(mapIt = map->begin(); mapIt != map->end(); ++mapIt)
	{
		mapIt->second = getRecognizingRegExpFromConstants(mapIt->second.substr(1));
		//std::cout<<std::endl<<"2: "<<(mapIt->second)<<std::endl;
	}

	return map;
}

double UnitRecognizer::getSIValue(std::string unit)
{
	for(int i=0; i<units->size(); ++i)
	{
		std::string r = "("+units->at(i).constant + std::string(ADDSTR)+")";
		//getRecognizingRegExpFromConstants(units->at(i).constant);
		boost::regex re(r);
		if(boost::regex_search(unit.begin(), unit.end(), re))
		{
			std::string value = boost::regex_replace(unit, re, "");
			//std::cout<<"val:"<<value<<"regexp:"<<re<<std::endl;
			//std::cout<<"splitted:"<<value<<"\n";

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
