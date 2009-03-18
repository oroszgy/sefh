#pragma once
#include "ConfigFileReader.h"
#include <map>
#include "Unit.h"
#include "NumberFormats.h"
#include <boost\regex.hpp>
#include <string>

class UnitRecognizer
{
public:
	UnitRecognizer(ConfigFileReader* reader);
	~UnitRecognizer();

	std::string getRecognizingRegExpFromConstants(std::string);
	std::string getRecognizingRegExp();
	double getSIValue(std::string);
	std::string getTypeOfMeasure(std::string);
	std::map<std::string, std::string>* getUnitsRecognizingRegexps();

private:
	std::vector<Unit>* units;
	std::vector<std::string>* separators;
	std::string decSep;
};
