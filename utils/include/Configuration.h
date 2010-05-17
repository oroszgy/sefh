#pragma once
#include "Unit.h"
#include <iostream>
#include <vector>

namespace com
{
namespace sefh
{
namespace utils
{
/**
 * Stores the configuration properties of the additional libraries for the indri
 * such as unit recognizer, hungarian stemmer...
 */
class Configuration
{
public:
	static Configuration* getDefault();
	~Configuration();

	/**
	 * Returns the units, which is set to be recognized.
	 */
	std::vector<com::sefh::unitrecognition::Unit>* getUnits();
	/**
	 * Returns the separators, which can separate the elements of an integer.
	 * e.g ' ' -> 1 000 is a number
	 */
	std::vector<std::string>* getSeparators();
	/**
	 * Returns a character which denotes the decimal point.
	 */
	std::string getDecimalSeparator();
	/**
	 * Returns the dateformat strings.
	 */
	std::vector<std::string>* getDateFormatStrings();

	std::string getFileType();

private:
	Configuration(std::string fileName);
	std::vector<std::string>* separators;
	std::string decimalSeparator;
	std::vector<com::sefh::unitrecognition::Unit>* units;
	std::vector<std::string>* dateFormats;

	std::string filetype;

	void parseFile(std::string fileName);

	static Configuration* defaultInstance;
};

}
}
}
