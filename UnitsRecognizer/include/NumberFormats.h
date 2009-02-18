#pragma once
#include<string>

class NumberFormats
{
public:
	static NumberFormats* getNumberFormatFromSeparators(std::string);
	std::string getRegExpString();
	~NumberFormats(void);
private:
	NumberFormats(std::string separators);
	void createFormatStr(std::string sep);

	std::string formatString;
};
