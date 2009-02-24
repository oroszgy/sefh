#pragma once
#include <string>
#include <queue>
#include <boost/regex.hpp>

class NumberFormats
{
public:
	static double convertToDouble(std::string decimalSep, std::string unit);
	static NumberFormats* getNumberFormatFromSeparators(std::string);
	std::string getRegExpString();
	~NumberFormats(void);
private:
	NumberFormats(std::string separators);
	void createFormatStr(std::string sep);
	static bool isInt(char c);

	std::string formatString;
};
