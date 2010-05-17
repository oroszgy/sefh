#include "../include/Configuration.h"
#include "../include/xmlParser.h"
#include "../include/path.h"

using namespace com::sefh::utils;

Configuration* Configuration::defaultInstance = NULL;

Configuration::Configuration(std::string fileName)
{
	parseFile(fileName);
}

Configuration::~Configuration()
{
}

Configuration* Configuration::getDefault()
{
	if(defaultInstance == NULL)
	{
		//TODO:: nem elég általános
	defaultInstance = new Configuration(CONF);
	}

	return defaultInstance;
}

void Configuration::parseFile(std::string fileName)
{

	XMLNode xMainNode = XMLNode::openFileHelper(fileName.c_str(), "UDML");

	units = new std::vector<com::sefh::unitrecognition::Unit>();

	std::string type, constant, multiplierStr;
	int i=0; char* p; double multiplier;
	XMLNode unitsNode = xMainNode.getChildNode("Units");
	XMLNode unitNode = unitsNode.getChildNode("Unit",0);
	while(!unitNode.isEmpty())
	{
		type = unitNode.getAttribute("type");
		multiplierStr = unitNode.getAttribute("multiplier");
		constant = unitNode.getText();

		multiplier = strtod(multiplierStr.c_str(),&p);
		units->push_back(com::sefh::unitrecognition::Unit(type,constant, multiplier));

		++i;
		unitNode = unitsNode.getChildNode("Unit", i);
	}

	//Szükséges, hogy az XML fájlban a a ' ' helyett '\s' legyen és hasonlóan
	//minden karaktersotozatnak reguláris alakja
	separators = new std::vector<std::string>();
	XMLNode separatorsNode= xMainNode.getChildNode("Separators");
	i=0; std::string isDec;
	XMLNode sepNode = separatorsNode.getChildNode("sep",i);
	while(!sepNode.isEmpty())
	{
		isDec = sepNode.getAttribute("isDecimal");

		if(isDec == "true")
		{
			decimalSeparator = sepNode.getText();
		}
		else
		{
			separators->push_back(sepNode.getText());
		}

		++i; sepNode = separatorsNode.getChildNode("sep", i);
	}

	dateFormats = new std::vector<std::string>();
	XMLNode dateNode = xMainNode.getChildNode("Dates");
	i=0; std::string tmpR;
	XMLNode dateFormatNode = dateNode.getChildNode("date", i);
	while(!dateFormatNode.isEmpty())
	{
		tmpR = dateFormatNode.getText();
		dateFormats->push_back( tmpR );

		++i; dateFormatNode = dateNode.getChildNode("date", i);
	}
}

std::vector<com::sefh::unitrecognition::Unit>* Configuration::getUnits()
{
	return units;
}

std::vector<std::string>* Configuration::getSeparators()
{
	return separators;
}

std::string Configuration::getDecimalSeparator()
{
	return decimalSeparator;
}

std::vector<std::string>* Configuration::getDateFormatStrings()
{
	return dateFormats;
}
