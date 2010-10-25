#include <iostream>
#include "../include/FieldAnnotator.h"

int main(int args, char** argv)
{
	if(args <3)
	{
		std::cout<<"Usage:\n"+std::string(argv[0])+" [fileName] [toFileName]\n";
		return -1;
	}

	com::sefh::utils::FieldAnnotator::doReplace(argv[1], argv[2]);

	std::cout<<argv[1]<< " is annotated and copied to "<<argv[2]<<"\n";

	return 0;
}

