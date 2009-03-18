#pragma once
#include <string>
#include <queue>
#include <boost/regex.hpp>

class NumberFormats
{
public:
	static double writtenNumberToDouble(std::string input);
	static double convertToDouble(std::string decimalSep, std::string unit);
	static NumberFormats* getNumberFormatFromSeparators(std::string);
	std::string getRegExpString();
	~NumberFormats(void);
private:
	NumberFormats(std::string separators);
	void createFormatStr(std::string sep);
	static bool isInt(char c);
	std::string formatString;

	static int partOfNumberValue(std::string);
	static char* digits[10];
	static char* tens[12];
	static char* hundred;
	static char* thousand;
	static char* million;
	static char* milliard;
};
