#pragma once
#include "xmlParser.h"
#include "Unit.h"
#include <iostream>
#include <vector>

class ConfigFileReader
{
public:
	ConfigFileReader(std::wstring fileName);
	~ConfigFileReader();

	std::vector<Unit>* getUnits();
	std::vector<std::string>* getSeparators();
	std::string getDecimalSeparator();

private:
	std::vector<std::string>* separators;
	std::string decimalSeparator;
	std::vector<Unit>* units;

	void parseFile(std::wstring fileName);
};
