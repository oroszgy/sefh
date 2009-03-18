// _testDate.cpp : Defines the entry point for the console application.
//
#include "FileCompleter.h"


int main(int argc, char **argvs)
{
	if(argc<2)
	{
		std::cout<<"Not enough arguments!\n";
		return 0;
	}
	FileCompleter f;
	std::string filename(argvs[1]);

	f.doReplace(filename);
	
	std::cout<<"Done!\n";
	return 0;
}

