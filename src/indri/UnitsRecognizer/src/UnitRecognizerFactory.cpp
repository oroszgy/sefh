#include "..\include\UnitRecognizerFactory.h"

UnitRecognizer* UnitRecognizerFactory::getDefault()
{
	/*if(defaultInstance == NULL)
	{
		ConfigFileReader* cfr = new ConfigFileReader(L"unit.txt");
		defaultInstance = new UnitRecognizer(cfr);
	}

	return defaultInstance;*/
	
	ConfigFileReader* cfr = ConfigFileReader::getDefault();
	return  new UnitRecognizer(cfr);
	
}
