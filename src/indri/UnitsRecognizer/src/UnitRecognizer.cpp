#include "..\include\UnitRecognizer.h"

UnitRecognizer::UnitRecognizer(ConfigFileReader* reader)
{
	units = reader->getUnits();
}

UnitRecognizer::~UnitRecognizer()
{
}

//TODO:: lekezelni azt az esetet amikor nincs semmi
std::string UnitRecognizer::getUnitRecognizingRegexp()
{
	NumberFormats* nf = NumberFormats::getNumberFormatFromSeparators("\\.");
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
			//m�k�dik, �s ha igen, akkor mi�rt is van sz�ks�g�nk a separatorsra?
			//TODO: meg kellene k�l�nb�ztetni 2 f�l�t... vagy azt mondani, hogy a sep csak
			//az elv�laszt�ra vonatkozik
			//TODO:: konverzi�

			//a tizedes elv�laszt� a '.'
			boost::regex re(getUnitRecognizingRegexp());
			std::string value = boost::regex_replace(unit, re, "$1");
			
			return atof(value.c_str());
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
