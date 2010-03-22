#pragma once
#include <string>

#define itoa com::sefh::utils::StringConverter::iToA

namespace com
{
namespace sefh
{
namespace utils
{

/**
 * Utility module which implements seberal useful string conversation methods.
 */
class StringConverter
{
public:
	/**
	 * The non-ansi itoa implementation.
	 */
	static char* iToA(int value, char* str, int radix);
	static bool isPrefix(std::string substr, std::string word);
#ifdef _GLIBCXX_USE_WCHAR_T
	std::wstring toWstring(std::string str);
	std::string toString(std::wstring str);
#endif
private:
	StringConverter(){}
};

}
}
}

