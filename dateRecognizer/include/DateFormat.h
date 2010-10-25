#pragma once
#include <vector>
#include <boost/regex.hpp>

namespace com
{
namespace sefh
{
namespace daterecognition
{
/**
 * Stores a a date format, that is a way of writing a date.
 *
 * e.g. the 20th of February 2008 can be written as 2008.02.20., and the
 * belonging format is yyyy.mm.dd.
 */
class DateFormat
{
public:
	/**
	 * Returns the existing instances of the class.
	 */
	static std::vector<DateFormat>* getInstances();
	~DateFormat();

	DateFormat create(std::string);

	std::string getSimpleRecognizerString();
	/**
	 * Returns a regular expression, which can be used for manipulating a
	 * corresponding string
	 */
	boost::regex getRecognizerRegExp();
	/**
	 * Returns a regular expression, which can be used for manipulating a
	 * corresponding string
	 */
	std::string getRecognizerString();
	/**
	 * If the input is a date string given in the specified format,
	 * it returns with the month.
	 */
	std::string getMonth(std::string date);
	/**
	 * If the input is a date string given in the specified format,
	 * it returns with the year.
	 */
	std::string getYear(std::string date);
	/**
	 * If the input is a date string given in the specified format,
	 * it returns with the day.
	 */
	std::string getDay(std::string date);

	/**
	 * If the input is a date string given in the specified format,
	 * it returns with the number of the month
	 */
	std::string getYearIntegrString(std::string date);
	/**
	 * If the input is a date string given in the specified format,
	 * it returns with the number of the month
	 */
	std::string getMonthIntegerString(std::string date);
	/**
	 * If the input is a date string given in the specified format,
	 * it returns with the number of the month
	 */
	std::string getDayIntegerString(std::string date);

private:
	DateFormat(std::string formatString, std::string filetype);
	int yearPos, monthPos, dayPos;
	std::string recognizerRegExp;
	std::string xmlrecognizerRegExp;
	std::string formatString;
	bool isNumericMonth;
	std::string filetype;

	void _parseDateFormat(std::string formatString);
	void _setRegExpString(std::string formatString);
	void _setTagsPositions(int yearStart, int monthStart, int dayStart);
	std::string getStringAtPos(int pos, std::string date);

	static std::string XML;
	static std::string TXT;

	static std::string january;
	static std::string february;
	static std::string march;
	static std::string april;
	static std::string may;
	static std::string june;
	static std::string july;
	static std::string august;
	static std::string september;
	static std::string october;
	static std::string november;
	static std::string december;

	static std::string jan;
	static std::string feb;
	static std::string mar;
	static std::string apr;
	static std::string may_short;
	static std::string jun;
	static std::string jul;
	static std::string aug;
	static std::string sep;
	static std::string oct;
	static std::string nov;
	static std::string dec;
};
}
}
}

