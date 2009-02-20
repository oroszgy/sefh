#pragma once
#include "ConfigFileReader.h"
#include <vector>
#include "Unit.h"
#include "NumberFormats.h"
#include <boost\regex.hpp>
#include <string>

class UnitRecognizer
{
public:
	UnitRecognizer(ConfigFileReader* reader);
	~UnitRecognizer();

	std::string getUnitRecognizingRegexp();
	double getSIValue(std::string);
	std::string getTypeOfMeasure(std::string);

private:
	std::vector<Unit>* units;
	std::vector<std::string>* separators;
	std::string decSep;
};
