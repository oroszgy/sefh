#include <iostream>
#include "../include/FieldAnnotator.h"

int main(int args, char** argv)
{
	if(args <2)
	{
		std::cout<<"Usage:\n"+std::string(argv[0])+" [fileName]";
		return -1;
	}

	com::sefh::utils::FieldAnnotator::doReplace(argv[1]);

	return 0;
}

