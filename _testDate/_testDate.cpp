// _testDate.cpp : Defines the entry point for the console application.
//
#include "DateFormats.h"
#include "FileCompleter.h"
#include <boost/regex.hpp>
#include "DateFormat.h"


int main(int argc, char **argvs)
{
	if(argc<3)
		return 0;
	
	FileCompleter f;
	std::string filename(argvs[1]);
	std::string dateFile(argvs[2]);

	DateFormats* df = new DateFormats();
	df->setSourceFile(dateFile);

	f.doReplace(filename, df);
	
	delete df;
	return 0;
}

