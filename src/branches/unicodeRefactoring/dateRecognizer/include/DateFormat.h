#pragma once
#include <vector>
#include <boost\regex.hpp>
#include "ConfigFileReader.h"

class DateFormat
{
public:
	static std::vector<DateFormat>* getInstances();
	~DateFormat();

	boost::regex getRecognizerRegExp();
	std::string getRecognizerString();
	std::string getMonth(std::string date);
	std::string getYear(std::string date);
	std::string getDay(std::string date);

	std::string getYearIntegrString(std::string date);
	std::string getMonthIntegerString(std::string date);
	std::string getDayIntegerString(std::string date);
	
private:
	DateFormat(std::string formatString);
	int yearPos, monthPos, dayPos;
	std::string recognizerRegExp;
	std::string formatString;
	bool isNumericMonth;

	void _parseDateFormat(std::string formatString);
	void _setRegExpString(std::string formatString);
	void _setTagsPositions(int yearStart, int monthStart, int dayStart);
	std::string getStringAtPos(int pos, std::string date);
};
