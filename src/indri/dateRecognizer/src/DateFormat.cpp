#include "..\include\DateFormat.h"
#include <math.h>

DateFormat::DateFormat(std::string _formatString)
{
	isNumericMonth=true;
	formatString = _formatString;
	_parseDateFormat(_formatString);
}

DateFormat::~DateFormat()
{
}

std::vector<DateFormat>* DateFormat::getInstances()
{
	ConfigFileReader* cfr = ConfigFileReader::getDefault();
	std::vector<std::string>* dfs = cfr->getDateFormatStrings();
	std::vector<DateFormat>* ret = new std::vector<DateFormat>();
	for(int i=0; i<dfs->size(); ++i)
	{
		ret->push_back(*(new DateFormat(dfs->at(i))));
	}

	return ret;
}

boost::regex DateFormat::getRecognizerRegExp()
{
	return boost::regex(recognizerRegExp);
}

std::string DateFormat::getDay(std::string date)
{
	return getStringAtPos(dayPos, date);
}

std::string DateFormat::getMonth(std::string date)
{
	return getStringAtPos(monthPos, date);
}

std::string DateFormat::getYearIntegrString(std::string date)
{
	std::string year = getYear(date);
	if(year.length() < 4)
		return "19" + year;
	else
		return year;
}

std::string DateFormat::getDayIntegerString(std::string date)
{
	std::string day = getDay(date);
	/*if(day.length() <2)
		return "0" + day;
	else */
		return day;
}

std::string DateFormat::getMonthIntegerString(std::string date)
{
	if(isNumericMonth)
		return getMonth(date);

	std::string monthStr = getMonth(date).substr(0,3);
	char first = monthStr[0];

	int monthNum;

	switch(first)
	{
	case 'j':
		if(monthStr=="jan")
			monthNum=1;
		else if(monthStr=="jún")
			monthNum=6;
		else if(monthStr=="júl")
			monthNum=7;
		break;
	case 'f':
		monthNum=2;
		break;
	case 'm':
		if(monthStr == "már")
			monthNum = 3;
		else if(monthStr == "máj")
			monthNum = 5;
		break;
	case 'á':
		monthNum=4;
		break;
	case 'a':
		monthNum=8;
		break;
	case 's':
		monthNum=9;
		break;
	case 'o':
		monthNum=10;
		break;
	case 'n':
		monthNum=11;
		break;
	case 'd':
		monthNum=12;
		break;
	}

	char* buf = new char[3];
	return std::string(itoa(monthNum,buf,10));
}

std::string DateFormat::getYear(std::string date)
{
	return getStringAtPos(yearPos, date);
}

std::string DateFormat::getStringAtPos(int pos, std::string date)
{
	std::string ret;
	std::string posStr = "$";
	char buffer[5];
	itoa(pos, buffer, 10);
	posStr += buffer;
	ret=boost::regex_replace(date,boost::regex(recognizerRegExp), posStr);
	return ret;
}

void DateFormat::_parseDateFormat(std::string formatString)
{
	//TODO: encoding?
	_setRegExpString(formatString);
}

void DateFormat::_setRegExpString(std::string dateFormat)
{
	std::string date(dateFormat);

	//TODO: extract constants to local variables

	int ys, ye, ms, ds, de, yc;
	//Replacing year with nums
	ys = dateFormat.find_first_of("y");
	ye = dateFormat.find_last_of("y");
	yc = ye-ys;
	date.replace(ys, yc + 1, "([0-9]{1,4})");

	//Replacing days
	ds = date.find_first_of("d");
	de = date.find_last_of("d");
	if(ds == de)
	{
		date.replace(ds,1,"([0-9]{1,2})");
	}
	else
	{
		date.replace(ds, de-ds+1, "([0-9]{2})");
	}

	//Replacing month with nums
	ms = date.find_first_of("m");
	if(date.substr(ms+1,1) == "m")
	{
		date.replace(ms,2,"([0-9]{2})");
	}
	else if(date.substr(ms,5) == "month")
	{
		std::string monthRegexp = 
			"(január|február|március|április|május|június|július|augusztus|szeptember|október|november|december)";
		date.replace(ms,5, monthRegexp);
		isNumericMonth = false;
	}
	else if(date.substr(ms,3) =="mon")
	{
		std::string mRegexp = "(jan|febr|márc|ápr|máj|jún|júl|aug|szept|okt|nov|dec)";
		date.replace(ms,3, mRegexp);
		isNumericMonth = false;
	}
	else
	{
		date.replace(ms,1,"([0-9]{1,2})");
	}
	
	//TODO: replace other non-permitted strings
	boost::regex dotRegexp("\\.");
	date = boost::regex_replace(date, dotRegexp, "\\\\.");	
	boost::regex spaceRegexp(" ");
	date = boost::regex_replace(date, spaceRegexp, "\\\\s");

	
	recognizerRegExp = date;

	_setTagsPositions(ys,ms,ds);
}

void DateFormat::_setTagsPositions(int yearStart, int monthStart, int dayStart)
{
	if(yearStart<monthStart)
	{
		if(yearStart<dayStart)
		{
			yearPos = 1;
			if(monthStart<dayStart)
			{
				monthPos = 2;
				dayPos = 3;
			}
			else if(monthStart>dayStart)
			{
				dayPos = 2;
				monthPos = 3;
			}

		}
		else if(yearStart > dayStart)
		{
			dayPos = 1;
			yearPos = 2;
			monthPos = 3;
		}
	}
	else if(yearStart>monthStart)
	{
		if(dayStart<monthStart)
		{
			dayPos = 1;
			monthPos = 2;
			yearPos = 3;
		}
		else if(yearStart<dayStart)
		{
			monthPos=1;
			yearPos = 2;
			dayPos = 3;
		}
		else if(yearStart>dayStart && dayStart>monthStart)
		{
			monthPos=1;
			dayPos=2;
			yearPos=3;
		}
	}
}


std::string DateFormat::getRecognizerString()
{
	return std::string(recognizerRegExp);
}