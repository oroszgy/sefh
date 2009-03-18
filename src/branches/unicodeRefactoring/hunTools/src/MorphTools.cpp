//#include "../include/stdafx.h"
#include "../include/MorphTools.h"
#include "../include/stem2005_export.h"
#include "../include/stem2005_options.h"
#include <string>
#include <iostream>
#include <windows.h>
#include <math.h>

#ifdef UNICODE
#include <wchar.h>
#endif

MorphTools::MorphTools()
{
	id=-1;
}

MorphTools::~MorphTools()
{
}

#ifdef UNICODE
int MorphTools::init(unsigned short *dllName, unsigned short *lexPath, int languageCode)
{
	//init
	HINSTANCE dll_instance = (HINSTANCE)0;
	p_initW = (ptf_initW)0;
	p_close = (ptf_close)0;
	p_stemW = (ptf_stemW)0;
	p_get_synonimsW = (ptf_get_synonimsW)0;

	dll_instance=LoadLibraryW((LPCWSTR)dllName);

	// verify if dll is loaded successfully
	if(dll_instance==(HINSTANCE)0){
		return -1;
	}

	//get functions
	p_initW=(ptf_initW)GetProcAddress(dll_instance,"initW");
	p_stemW=(ptf_stemW)GetProcAddress(dll_instance,"stemW");
	p_close=(ptf_close)GetProcAddress(dll_instance,"close");
	p_get_synonimsW=(ptf_get_synonimsW)GetProcAddress(dll_instance,"get_synonimsW");

	//verify function pointers
	if((p_close==(ptf_close)0) ||
		(p_initW==(ptf_initW)0) ||
		(p_stemW==(ptf_stemW)0) ||
		(p_get_synonimsW==(ptf_get_synonimsW)0)){
		FreeLibrary(dll_instance);
		return -2;
	}

	id = p_initW(lexPath, languageCode, 0);
	if(id<0) return -1;

	return 0;
}

/* P: |word| >0 and !"\n" is in  word */
/* Q: return = null | stem */
std::vector<std::wstring>* MorphTools::getStems(std::wstring inData)
{
	unsigned short out[512];
	int only_stem = SHOW_STEM_ONLY | SHOW_COMPOUND_POSITIONS | FILTER_STEM;

	int ret = p_stemW(id, (const unsigned short*)inData.c_str(), out, sizeof(out)/sizeof(out[0]), only_stem);
	if (ret == 0)
	{
		return splitString((wchar_t*)out, ',', '+');
	}
	else
		return NULL;
}

std::vector<std::wstring>* MorphTools::getSynonyms(std::wstring inData)
{
	unsigned short out[1024];
	int only_stem = SHOW_STEM_ONLY | SHOW_COMPOUND_POSITIONS | FILTER_STEM;

	int ret;

	ret = p_get_synonimsW(id, (const unsigned short*)inData.c_str(), out, sizeof(out)/sizeof(out[0]), 0);

	if(ret==0)
	{
		return splitString((wchar_t*)out, ',', '+');
	}

	return NULL;
}

std::vector<std::wstring>* MorphTools::splitString(wchar_t* word, wchar_t ch1, wchar_t ch2)
{
	std::vector<std::wstring>* ret = new std::vector<std::wstring>();
	std::wstring s = word;
	int loc = findNextPos(s, ch1, ch2);
	while(loc != std::wstring::npos)
	{
		ret->push_back(s.substr(0, loc));

		s = s.substr(loc + 1);
		loc = findNextPos(s, ch1, ch2);
	}
	ret->push_back(s);

	return ret;
}

int MorphTools::findNextPos(std::wstring s, wchar_t ch1, wchar_t ch2) 
{
	int loc1 = s.find(ch1);
	int loc2 = s.find(ch2);
	if(loc1==std::wstring::npos)
		return loc2;
	if(loc2==std::wstring::npos)
		return loc1;
	int loc = loc1 < loc2 ? loc1 : loc2;
	return loc;
}
#endif

#ifndef UNICODE
int MorphTools::init(char* dllName, char* lexPath, int langCode, int codePage)
{
          HINSTANCE dll_instance = (HINSTANCE)0;
          p_init = (ptf_init)0;
          p_close = (ptf_close)0;
          p_stem = (ptf_stem)0;
          p_get_synonims = (ptf_get_synonims)0;

          dll_instance=LoadLibrary(dllName);

          // verify if dll is loaded successfully
          if(dll_instance==(HINSTANCE)0){
                  return -1;
          }
          //get functions
          p_init=(ptf_init)GetProcAddress(dll_instance,"init");
          p_close=(ptf_close)GetProcAddress(dll_instance,"close");
          p_stem=(ptf_stem)GetProcAddress(dll_instance,"stem");
          p_get_synonims=(ptf_get_synonims)GetProcAddress(dll_instance,"get_synonims");

          //verify function pointers
          if((p_init==(ptf_init)0) ||
                  (p_close==(ptf_close)0) ||
                  (p_stem==(ptf_stem)0) ||
                  (p_get_synonims==(ptf_get_synonims)0)){
                  FreeLibrary(dll_instance);
                  return -2;
          }

          id = p_init(lexPath, langCode, codePage, 0);
          if(id<0) return -1;

          return 0;
}

std::vector<std::string>* MorphTools::getStems(std::string word)
{
	char out[512];
	int only_stem = SHOW_STEM_ONLY | SHOW_COMPOUND_POSITIONS | FILTER_STEM;

	int ret = p_stem(id, word.c_str(), out, sizeof(out)/sizeof(out[0]), only_stem);
	if (ret == 0)
	{
		return splitString(out, ',');
	}
	else
		return NULL;
}
std::vector<std::string>* MorphTools::getSynonyms(std::string word)
{
    char out[1024];
    int only_stem = SHOW_STEM_ONLY | SHOW_COMPOUND_POSITIONS | FILTER_STEM;
    int ret;

    ret = p_get_synonims(id, word.c_str(), out, sizeof(out)/sizeof(out[0]), 1);

    if(ret==0)
    {
            return splitString(out, ',');
    }

    return NULL;
}
std::vector<std::string>* MorphTools::splitString(char* word, char ch)
{
	std::vector<std::string>* ret = new std::vector<std::string>();
	std::string s = word;
	unsigned int loc = s.find(ch);
	while(loc != std::string::npos)
	{
			ret->push_back(s.substr(0, loc));

			s = s.substr(loc + 1);
			loc = s.find(ch);
	}
	ret->push_back(s);

	return ret;
}
#endif
