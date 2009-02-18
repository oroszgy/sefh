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
	
	units = new std::vector<Unit*>();

	std::wstring type, constant, multiplierStr;
	int i=0; char* p; double multiplier;
	XMLNode unitNode = xMainNode.getChildNode(_T("Unit"),0);
	while(!unitNode.isEmpty())
	{
		type = unitNode.getAttribute(_T("type"));
		multiplierStr = unitNode.getAttribute(_T("multiplier"));
		constant = unitNode.getText();
		
		multiplier = strtod(StringCoverter::WStringToString(multiplierStr).c_str(),&p);
		units->push_back(new Unit(StringCoverter::WStringToString(type),
			StringCoverter::WStringToString(constant), multiplier));

		++i;
		unitNode = xMainNode.getChildNode(_T("Unit"), i);
	}

}

std::vector<Unit*>* ConfigFileReader::getUnits()
{
	return units;
}