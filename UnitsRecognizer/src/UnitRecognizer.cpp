#include "..\include\UnitRecognizer.h"

UnitRecognizer::UnitRecognizer(ConfigFileReader* reader)
{
	units = reader->getUnits();
	separators = reader->getSeparators();
	decSep = reader->getDecimalSeparator();
}

UnitRecognizer::~UnitRecognizer()
{
}

//TODO:: lekezelni azt az esetet amikor nincs semmi
std::string UnitRecognizer::getUnitRecognizingRegexp()
{
	std::string sep;
	for(int i=0; i<separators->size(); ++i)
	{
		sep+=separators->at(i);
	}

	NumberFormats* nf = NumberFormats::getNumberFormatFromSeparators(sep);
	std::string REStr = "("+nf->getRegExpString()+")";
	REStr+="\\s*(";
	
	for(int i=0; i<units->size(); ++i)
	{
		REStr+=units->at(i).constant;
		REStr+="|";
	}

	REStr[REStr.length()-1]=')';
	REStr+="$";
	return REStr;
}

double UnitRecognizer::getSIValue(std::string unit)
{
	for(int i=0; i<units->size(); ++i)
	{
		int found = unit.find(units->at(i).constant);
		if(found != std::string::npos)
		{
			//mûködik, és ha igen, akkor miért is van szükségünk a separatorsra?
			//TODO: meg kellene különböztetni 2 félét... vagy azt mondani, hogy a sep csak
			//az elválasztóra vonatkozik
			//TODO:: konverzió

			//a tizedes elválasztó a '.'
			////////////elvileg a fentiek mûködnek, ellenõrizd le
			boost::regex re(getUnitRecognizingRegexp());
			std::string value = boost::regex_replace(unit, re, "$1");
			
			return NumberFormats::convertToDouble(decSep[0], value);
		}
	}

	return 0;
}

std::string UnitRecognizer::getTypeOfMeasure(std::string unit)
{
	for(int i=0; i<units->size(); ++i)
	{
		if(unit.find(units->at(i).constant) != std::string::npos)
			return units->at(i).type;
	}
		
	return "";
}
