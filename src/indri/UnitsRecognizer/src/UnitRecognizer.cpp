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

std::string UnitRecognizer::getUnitsRecognizingRegExp()
{
	std::string unitConstants;
	for(int i=0; i<units->size(); ++i)
	{
		unitConstants+=units->at(i).constant;
		if(i<units->size()-1)
			unitConstants+="|";
	}
	return getUnitRecognizingRegExpFromConstants(unitConstants);
}

//TODO:: lekezelni azt az esetet amikor nincs semmi
std::string UnitRecognizer::getUnitRecognizingRegExpFromConstants(std::string unitConstants)
{
	std::string sep;
	for(int i=0; i<separators->size(); ++i)
	{
		sep += separators->at(i);
	}
	sep += decSep;

	NumberFormats* nf = NumberFormats::getNumberFormatFromSeparators(sep);
	std::string REStr = "(" + nf->getRegExpString() + ")";
	REStr += "\\s*(";
	
	REStr += unitConstants;

	REStr += ')';
	//REStr += "$";
	return REStr;
}

std::map<std::string, std::string>* UnitRecognizer::getUnitsRecognizingRegexps()
{
	std::map<std::string, std::string>* map = new std::map<std::string, std::string>();
	std::vector<Unit>::iterator vecIt;
	for(vecIt = units->begin(); vecIt != units->end(); ++vecIt)
	{
		(*map)[(*vecIt).type] += "|" + (*vecIt).constant;
	}

	std::map<std::string, std::string>::iterator mapIt;
	for(mapIt = map->begin(); mapIt != map->end(); ++mapIt)
	{
		mapIt->second = getUnitRecognizingRegExpFromConstants(mapIt->second.substr(1));
	}

	return map;
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
			boost::regex re(getUnitsRecognizingRegExp());
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
