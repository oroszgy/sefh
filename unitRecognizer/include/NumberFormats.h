#pragma once
#include <string>
#include <queue>

namespace com
{
namespace sefh
{
namespace unitrecognition
{
/**
 * Utilty class, which is used to recognize numbers in different formats.
 */
class NumberFormats
{
public:
	/**
	 * Returns a double number, which is written [in natural language] in the input.
	 */
	static double writtenNumberToDouble(std::string input);
	/**
	 * Returns with a double number corresponding to the input.
	 */
	static double convertToDouble(std::string decimalSep, std::string unit);
	/**
	 * Generator method.
	 */
	static NumberFormats* getNumberFormatFromSeparators(std::string);
	/**
	 * Returns a regular expression, which can be used to recognize number formats.
	 */
	std::string getRegExpString();
	~NumberFormats(void);
	static int partOfNumberValue(std::string);
private:
	NumberFormats(std::string separators);
	void createFormatStr(std::string sep);
	static bool isInt(char c);
	static bool isInt(std::string& str);
	std::string formatString;



	static char* digits[10];
	static char* tens[12];
	static char* hundred;
	static char* thousand;
	static char* million;
	static char* milliard;
	static char* thousandmilliard;
};
}
}
}
