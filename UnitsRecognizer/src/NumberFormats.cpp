#include "..\include\NumberFormats.h"

NumberFormats::NumberFormats(std::string sep)
{
	createFormatStr(sep);
}

NumberFormats::~NumberFormats(void)
{
}

//TODO:: mi a helyzet a '.'-tal illetve a '\s'-szel?
void NumberFormats::createFormatStr(std::string sep)
{
	if(sep == "")
		formatString = "\d+";
	else
		formatString ="^\d+(["+sep+"]{0,1}\d)*\d*$";
}

NumberFormats* NumberFormats::getNumberFormatFromSeparators(std::string sep)
{
	return new NumberFormats(sep);
}