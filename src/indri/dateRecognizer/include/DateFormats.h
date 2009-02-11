#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "DateFormat.h"

/* This class stores date formats. They can be converted into Regexp as well. 
Date formats are parsed from simple text files: dates are separated with new lines*/
class DateFormats
{
public:
	DateFormats();
	~DateFormats();
	void setSourceFile(std::string filePath);
	std::vector<DateFormat>* getDateFormats();
private:
	std::vector<DateFormat>* dates;

};
