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
	std::string test = fc->doUnitTransformation("balbalb asdfkl asdf\n 1000 kg �s 300 mg sat�bbi no meg 100 dkg");


}