//#include "../include/stdafx.h"
#include "../include/MorphToolsFactory.h"
#include "../include/MorphTools.h"

/* returns the default MorphTools obejct */
MorphTools* MorphToolsFactory::getDefault()
{
#ifdef UNICODE
	const wchar_t* DLL_PATH = L"stem2005.dll";
	const wchar_t* LEX_PATH = L"lex";
#endif
#ifndef UNICODE
	char* DLL_PATH = "stem2005.dll";
	char* LEX_PATH = "lex";
#endif


		MorphTools* morphToolsInstance = new MorphTools();
#ifdef UNICODE

		int ret = morphToolsInstance->init((unsigned short*)DLL_PATH,
			(unsigned short*)LEX_PATH, 1038);
#endif
#ifndef UNICODE
		int ret = morphToolsInstance->init(DLL_PATH,LEX_PATH, 1038, 852);
#endif
		if(morphToolsInstance->id>=0 && ret >=0)
			return morphToolsInstance;

	return NULL;
}
