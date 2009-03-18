#pragma once
#include "xmlParser.h"
#include "Unit.h"
#include <iostream>
#include <vector>

class ConfigFileReader
{
public:
	static ConfigFileReader* getDefault();
	~ConfigFileReader();

	std::vector<Unit>* getUnits();
	std::vector<std::string>* getSeparators();
	std::string getDecimalSeparator();
	std::vector<std::string>* getDateFormatStrings();

private:
	ConfigFileReader(std::wstring fileName);
	std::vector<std::string>* separators;
	std::string decimalSeparator;
	std::vector<Unit>* units;
	std::vector<std::string>* dateFormats;

	void parseFile(std::wstring fileName);

	static ConfigFileReader* defaultInstance;
};
