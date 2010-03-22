#include "../include/StringConverter.h"

using namespace com::sefh::utils;
char* StringConverter::iToA(int value, char* str, int radix) {
    static char dig[] =
        "0123456789"
        "abcdefghijklmnopqrstuvwxyz";
    int n = 0, neg = 0;
    unsigned int v;
    char* p, *q;
    char c;

    if (radix == 10 && value < 0) {
        value = -value;
        neg = 1;
    }
    v = value;
    do {
        str[n++] = dig[v%radix];
        v /= radix;
    } while (v);
    if (neg)
        str[n++] = '-';
    str[n] = '\0';
    for (p = str, q = p + n/2; p != q; ++p, --q)
        c = *p, *p = *q, *q = c;
    return str;
}

bool StringConverter::isPrefix(std::string substr, std::string word)
{
	return substr == word.substr(0,substr.length());
}

#ifdef _GLIBCXX_USE_WCHAR_T
std::wstring StringConverter::toWstring(std::string str)
{
	return std::wstring(str.begin(),str.end());
}

std::string StringConverter::toString(std::wstring wstr)
{
	return std::string(wstr.begin(), wstr.end());
}
#endif
