#include "..\include\DateFormats.h"
#include <boost/regex.hpp>

DateFormats::DateFormats()
{
}

DateFormats::~DateFormats()
{
	if(!dates)
		delete dates;
}

std::vector<DateFormat>* DateFormats::getDateFormats()
{
	std::vector<DateFormat>* ret = new std::vector<DateFormat>(*dates);
	return ret;
}


/*
 * Recognized language:
 * Date = Sep* Term Sep* Term Sep* Term Sep*
 * Term = Year | Month | Day
 * Year = yyyy | yy
 * Month = mm | m | month | mon
 * Day = dd | d
 * Separate = '.' | '-' | ' ' | '/' | '''
 */
void DateFormats::setSourceFile(std::string filePath)
{
	if(!dates)
		delete dates;
	dates = new std::vector<DateFormat>();

	//TODO:: általánosabb sorvége kezelés
	std::ifstream* inputFile;
	inputFile = new std::ifstream();
	inputFile->open(filePath.c_str());
	char* line = new char[1024];
	
	while(!inputFile->eof())
	{
		inputFile->getline(line,1024,'\n');
		
		dates->push_back(DateFormat(line));
	}
	inputFile->close();
	delete inputFile;
}