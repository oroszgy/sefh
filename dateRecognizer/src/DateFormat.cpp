#include "../include/DateFormat.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "StringConverter.h"
#include "Configuration.h"
#include "constants.h"

using namespace com::sefh::daterecognition;

std::string DateFormat::XML = "xml";
std::string DateFormat::TXT = "txt";

std::string DateFormat::january = "január";
std::string DateFormat::february = "február";
std::string DateFormat::march = "március";
std::string DateFormat::april = "április";
std::string DateFormat::may = "május";
std::string DateFormat::june = "június";
std::string DateFormat::july = "július";
std::string DateFormat::august = "augusztus";
std::string DateFormat::september = "szeptember";
std::string DateFormat::october = "október";
std::string DateFormat::november = "november";
std::string DateFormat::december = "december";

std::string DateFormat::jan = "jan";
std::string DateFormat::feb = "febr";
std::string DateFormat::mar = "márc";
std::string DateFormat::apr = "ápr";
std::string DateFormat::may_short = "máj";
std::string DateFormat::jun = "jún";
std::string DateFormat::jul = "júl";
std::string DateFormat::aug = "aug";
std::string DateFormat::sep = "szept";
std::string DateFormat::oct = "okt";
std::string DateFormat::nov = "nov";
std::string DateFormat::dec = "dec";

DateFormat::DateFormat(std::string _formatString, std::string ft)
{
	isNumericMonth=true;
	formatString = _formatString;
	_parseDateFormat(_formatString);
	filetype = ft;
}

DateFormat::~DateFormat()
{
}

std::vector<DateFormat>* DateFormat::getInstances()
{
	com::sefh::utils::Configuration* cfr = com::sefh::utils::Configuration::getDefault();
	std::vector<std::string>* dfs = cfr->getDateFormatStrings();
	std::vector<DateFormat>* ret = new std::vector<DateFormat>();
	for(size_t i=0; i<dfs->size(); ++i)
	{
		ret->push_back(*(new DateFormat(dfs->at(i), cfr->getFileType())));
	}

	return ret;
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
	std::string monthStr = getMonth(date);
	if(isNumericMonth)
		return monthStr;

	using namespace com::sefh::utils;
	if(StringConverter::isPrefix(monthStr, january))
		return "1";
	else if(StringConverter::isPrefix(monthStr, february))
			return "2";
	else if(StringConverter::isPrefix(monthStr, march))
			return "3";
	else if(StringConverter::isPrefix(monthStr, april))
			return "4";
	else if(StringConverter::isPrefix(monthStr, may))
			return "5";
	else if(StringConverter::isPrefix(monthStr, june))
			return "6";
	else if(StringConverter::isPrefix(monthStr, july))
			return "7";
	else if(StringConverter::isPrefix(monthStr, august))
			return "8";
	else if(StringConverter::isPrefix(monthStr, september))
			return "9";
	else if(StringConverter::isPrefix(monthStr, october))
			return "10";
	else if(StringConverter::isPrefix(monthStr, november))
			return "11";
	else if(StringConverter::isPrefix(monthStr, december))
			return "12";

	return "-1";

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
	//FIXME: year long should be the same as the count of the 'y'-s
	date.replace(ys, yc + 1, "([0-9]{4})");

	//Replacing days
	ds = date.find_first_of("d");
	de = date.find_last_of("d");
	if(ds == de)
	{
		//date.replace(ds,1,"([0-9]{1,2})");
		date.replace(ds,1, "(1|2|3|4|5|6|7|8|9|10|11|12|13|14|15|16|17|18|19|20|21|22|23|24|25|26|27|28|29|30|31)");
	}
	else
	{
		//date.replace(ds, de-ds+1, "([0-9]{2})");
		date.replace(ds,de-ds+1, "(01|02|03|04|05|06|07|08|09|10|11|12|13|14|15|16|17|18|19|20|21|22|23|24|25|26|27|28|29|30|31)");
	}

	//Replacing month with nums
	ms = date.find_first_of("m");
	if(date.substr(ms+1,1) == "m")
	{
		//date.replace(ms,2,"([0-9]{2})");
		date.replace(ms,2,"(01|02|03|04|05|06|07|08|09|10|11|12)");
	}
	else if(date.substr(ms,5) == "month")
	{
		std::string monthRegexp =
			"("+january+"|"+february+"|"+march+"|"+april+"|"+may+"|"
			+june+"|"+july+"|"+august+"|"+september+"|"+october+"|"+november
			+"|"+december+")";
		//char* buf = new char[monthRegexp.size()];
		//strcpy(buf, monthRegexp.c_str());
		//monthRegexp = _mbsrev((unsigned char*)buf);
		//TODO:: biztosan jól megy a kódolás?
		date.replace(ms,5, monthRegexp);
		isNumericMonth = false;
	}
	else if(date.substr(ms,3) =="mon")
	{
		std::string mRegexp = "("+jan+"|"+feb+"|"+mar+"|"+apr+"|"+may_short+"|"
		+jun+"|"+jul+"|"+aug+"|"+sep+"|"+oct+"|"+nov+"|"+dec+")";
		date.replace(ms,3, mRegexp);
		isNumericMonth = false;
	}
	else
	{
		//date.replace(ms,1,"([0-9]{1,2})");
		date.replace(ms,1,"(1|2|3|4|5|6|7|8|9|10|11|12)");
	}

	//TODO: replace other non-permitted strings
	boost::regex dotRegexp("\\.");
	date = boost::regex_replace(date, dotRegexp, "\\\\.");

	boost::regex spaceRegexp(" ");

	date += std::string(ADDSTR);


	/*
	 * Regex:
	 * (((<.+?>)(\s)*))(\d{2,4})(((<.+?>)|(\s))+)(január|február|március|április|május|június|július|augusztus|szeptember|október|november|december)(((<.+?>)|(\s))+)((1|2|3|4|5|6|7|8|9|10|11|12|13|14|15|16|17|18|19|20|21|22|23|24|25|26|27|28|29|30|31))(((<.+?>)(\s)*))
	 */

	std::string prefix, suffix, sep;

	prefix = std::string(PREFIX);
	suffix += std::string(SUFFIX);
	sep = std::string(DSEP);
	std::string xmldate = boost::regex_replace(date, spaceRegexp, sep);
	xmldate = prefix + xmldate + suffix;

	suffix = ADDSTR;
	//TODO: test it with xml and txt files as well.
	date = boost::regex_replace(date, spaceRegexp, "\\\\s");
	date += suffix;

	//Debug
	//std::cout << xmldate << std::endl;
	/*if(date[date.length()-1] == ')')
		date += "[^\\d]";*/


	recognizerRegExp = date;
	xmlrecognizerRegExp = xmldate;

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
	//std::cout<<filetype<<"\t"<<std::string(TXT)<<recognizerRegExp<<xmlrecognizerRegExp<<"\n";
	if(filetype == std::string(TXT))
		return std::string(recognizerRegExp);
	else
		return std::string(xmlrecognizerRegExp);
}

boost::regex DateFormat::getRecognizerRegExp()
{
	//Debug
	//std::cout<<recognizerRegExp;
	return boost::regex(getRecognizerString());
}

std::string DateFormat::getSimpleRecognizerString() {
	return std::string(recognizerRegExp);
}
