#include "..\include\ConfigFileReader.h"
#include "StringCoverter.h"

ConfigFileReader* ConfigFileReader::defaultInstance = NULL;

ConfigFileReader::ConfigFileReader(std::wstring fileName)
{
	parseFile(fileName);
}

ConfigFileReader::~ConfigFileReader()
{
}

ConfigFileReader* ConfigFileReader::getDefault()
{
	if(defaultInstance == NULL)
	{
	defaultInstance = new ConfigFileReader(L"e:\\teszt\\conf.xml");
	}

	return defaultInstance;
}

void ConfigFileReader::parseFile(std::wstring fileName)
{
	
	XMLNode xMainNode = XMLNode::openFileHelper(fileName.c_str(), _T("UDML"));
	
	units = new std::vector<Unit>();

	std::wstring type, constant, multiplierStr;
	int i=0; char* p; double multiplier;
	XMLNode unitsNode = xMainNode.getChildNode(_T("Units"));
	XMLNode unitNode = unitsNode.getChildNode(_T("Unit"),0);
	while(!unitNode.isEmpty())
	{
		type = unitNode.getAttribute(_T("type"));
		multiplierStr = unitNode.getAttribute(_T("multiplier"));
		constant = unitNode.getText();
		
		multiplier = strtod(StringConverter::WStringToString(multiplierStr).c_str(),&p);
		units->push_back(Unit(StringConverter::WStringToString(type),
			StringConverter::WStringToString(constant), multiplier));

		++i;
		unitNode = unitsNode.getChildNode(_T("Unit"), i);
	}

	//Szükséges, hogy az XML fájlban a a ' ' helyett '\s' legyen és hasonlóan
	//minden karaktersotozatnak reguláris alakja
	separators = new std::vector<std::string>();
	XMLNode separatorsNode= xMainNode.getChildNode(_T("Separators"));
	i=0; std::wstring isDec;
	XMLNode sepNode = separatorsNode.getChildNode(_T("sep"),i);
	while(!sepNode.isEmpty())
	{
		isDec = sepNode.getAttribute(_T("isDecimal"));
		
		if(isDec == L"true")
		{
			decimalSeparator = StringConverter::WStringToString(sepNode.getText());
		}
		else
		{
			separators->push_back(StringConverter::WStringToString(sepNode.getText()));	
		}

		++i; sepNode = separatorsNode.getChildNode(_T("sep"), i);
	}

	dateFormats = new std::vector<std::string>();
	XMLNode dateNode = xMainNode.getChildNode(_T("Dates"));
	i=0; std::string tmpR;
	XMLNode dateFormatNode = dateNode.getChildNode(_T("date"), i);
	while(!dateFormatNode.isEmpty())
	{
		tmpR = StringConverter::WStringToString(dateFormatNode.getText());
		dateFormats->push_back( tmpR );

		++i; dateFormatNode = dateNode.getChildNode(_T("date"), i);
	}
}

std::vector<Unit>* ConfigFileReader::getUnits()
{
	return units;
}

std::vector<std::string>* ConfigFileReader::getSeparators()
{
	return separators;
}

std::string ConfigFileReader::getDecimalSeparator()
{
	return decimalSeparator;
}

std::vector<std::string>* ConfigFileReader::getDateFormatStrings()
{
	return dateFormats;
}