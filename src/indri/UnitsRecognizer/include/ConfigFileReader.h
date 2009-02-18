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

	std::vector<Unit*>* getUnits();

private:
	std::string separators;
	std::vector<Unit*>* units;

	void parseFile(std::wstring fileName);
};
