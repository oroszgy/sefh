#pragma once
#include "UnitRecognizer.h"


class UnitRecognizerFactory
{
public:
	static UnitRecognizer* getDefault();
private:
	static UnitRecognizer* defaultInstance;
};
