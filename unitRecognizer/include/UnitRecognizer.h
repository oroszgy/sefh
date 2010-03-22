#pragma once
#include <vector>
#include <map>
#include <string>
#include "../../utils/include/Unit.h"

namespace com
{
namespace sefh
{
namespace unitrecognition
{
/**
 * Utility class which stores number formats, and can generate recognizing regular
 * expressions.
 */
class UnitRecognizer
{
public:
	~UnitRecognizer();

	/**
	 * Returns the default instance.
	 */
	static UnitRecognizer* getDefault();
	/**
	 * Returns a regular expression which can recognize the given unit.
	 */
	std::string getRecognizingRegExpFromConstants(std::string);
	/**
	 * Returns a regular expression which can recognize units.
	 */
	std::string getRecognizingRegExp();
	/**
	 * Returns the SI value of the stored unit.
	 */
	double getSIValue(std::string);
	/**
	 * Returns the type of the unit.
	 */
	std::string getTypeOfMeasure(std::string);
	/**
	 * Returns the unit recognition regular expressions.
	 */
	std::map<std::string, std::string>* getUnitsRecognizingRegexps();

private:
	UnitRecognizer();
	static UnitRecognizer* defaultInstance;
	std::vector<Unit>* units;
	std::vector<std::string>* separators;
	std::string decSep;
};
}
}
}

