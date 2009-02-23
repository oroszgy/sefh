#include <complex>
#include <iostream>

#include "ConfigFileReader.h"
#include "xmlParser.h"
#include "UnitRecognizer.h"
#include "FileCompleter.h"
#include <boost/regex.hpp>

int main()
{   

	FileCompleter* fc = new FileCompleter();
	std::string test = fc->doUnitTransformation("balbalb asdfkl asdf\n 1000 kg és 300 mg satöbbi no meg 100 dkg");


}