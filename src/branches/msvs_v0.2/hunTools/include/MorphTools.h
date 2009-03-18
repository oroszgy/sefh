#pragma once

#include "stem2005_export.h"
#include <string>
#include <vector>
#include <windows.h>
#include <iostream>
#include <string>


class MorphTools
{
public:
	MorphTools();
	~MorphTools();
	int id;

//TODO: implementálni a mind2 részt helyesen

#ifdef UNICODE
	int init(unsigned short*, unsigned short*, int);
	std::vector<std::wstring>* getStems(std::wstring word);
	std::vector<std::wstring>* getSynonyms(std::wstring word);

	std::vector<std::wstring>* splitString(wchar_t* word, wchar_t ch1, wchar_t ch2);
	int findNextPos(std::wstring s, wchar_t ch1, wchar_t ch2);

protected:
	ptf_initW p_initW;
	ptf_close p_close;
	ptf_stemW p_stemW;
	ptf_get_synonimsW p_get_synonimsW;
#endif

#ifndef UNICODE
	int init(char* dllName, char* lexPath, int langCode, int codePage);
	std::vector<std::string>* getStems(std::string word);
	std::vector<std::string>* getSynonyms(std::string word);
	std::vector<std::string>* splitString(char* word, char ch1, char ch2);
protected:
    ptf_init p_init;
    ptf_close p_close;
    ptf_stem p_stem;
    ptf_get_synonims p_get_synonims;
#endif

};

