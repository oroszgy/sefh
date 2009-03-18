#pragma once
#include <string>
#include <algorithm>

class StringConverter
{
public:
static std::wstring StringToWString(const std::string& s);
static std::string WStringToString(const std::wstring& s);
static std::wstring UTF8ToUnicode(const std::string& s);
static std::string UnicodeToUTF8(const std::wstring &wstr);

};
