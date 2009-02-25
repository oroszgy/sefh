//#include "../include/stdafx.h"
#include "../include/StringCoverter.h"
#include <string>
#include "atlbase.h"
#include "atlstr.h"
#include "comutil.h"

std::wstring StringConverter::StringToWString(const std::string& s)
{
	USES_CONVERSION;
	std::string temp(s.length(),L'û');
	std::copy(s.begin(), s.end(), temp.begin());
	CString cstring(temp.c_str());
	wchar_t* wstr = T2W(cstring.GetBuffer());
	cstring.ReleaseBuffer();
	return wstr;
}


std::string StringConverter::WStringToString(const std::wstring& s)
{
	USES_CONVERSION;
	CString cstring(s.c_str());
	std::string ss = std::string(CT2CA(cstring));
	return ss;
	//std::string temp(s.length(), ' ');
	//std::copy(s.begin(), s.end(), temp.begin());
	//return temp;
}

std::wstring StringConverter::UTF8ToUnicode(const std::string &s)
{
	wchar_t buffer[1000];
	MultiByteToWideChar(CP_UTF8, 0, s.c_str(), -1, buffer, 1000);
	std::wstring ret = buffer;
	return ret;
}

std::string StringConverter::UnicodeToUTF8(const std::wstring &wstr)
{
    // Convert a Unicode string to an ASCII string
    std::string strTo;
    char *szTo = new char[wstr.length() + 1];
    szTo[wstr.size()] = '\0';
    WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, szTo, (int)wstr.length(), NULL, NULL);
    strTo = szTo;
    delete[] szTo;
    return strTo;
}

