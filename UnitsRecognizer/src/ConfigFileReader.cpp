#include "..\include\ConfigFileReader.h"
#include "StringCoverter.h"

ConfigFileReader::ConfigFileReader(std::wstring fileName)
{
	parseFile(fileName);
}

ConfigFileReader::~ConfigFileReader()
{
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
		
		multiplier = strtod(StringCoverter::WStringToString(multiplierStr).c_str(),&p);
		units->push_back(Unit(StringCoverter::WStringToString(type),
			StringCoverter::WStringToString(constant), multiplier));

		++i;
		unitNode = unitsNode.getChildNode(_T("Unit"), i);
	}

	//Sz�ks�ges, hogy az XML f�jlban a a ' ' helyett '\s' legyen �s hasonl�an
	//minden karaktersotozatnak regul�ris alakja
	separators = new std::vector<std::string>();
	XMLNode separatorsNode= xMainNode.getChildNode(_T("Separators"));
	i=0; std::string isDec;
	XMLNode sepNode = separatorsNode.getChildNode(_T("sep"),i);
	while(!sepNode.isEmpty())
	{
		isDec = StringCoverter::WStringToString(sepNode.getAttribute(_T("isDecimal")));
		
		if(isDec == "true")
		{
			decimalSeparator = StringCoverter::WStringToString(sepNode.getText());
		}
		else
		{
			separators->push_back(StringCoverter::WStringToString(sepNode.getText()));	
		}

		++i; sepNode = separatorsNode.getChildNode(_T("sep"), i);
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