// testHunTools.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MorphToolsFactory.h"


void change(int& i) {
	int *j= new int(7);
	i=*j;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int i =6;
	change(i);

	std::cout<<i;
	
	//MorphTools* mt = MorphToolsFactory::getDefault();
	//std::vector<std::wstring>* t = mt->getStems(L"teniszütõket");
	return 0;
}



