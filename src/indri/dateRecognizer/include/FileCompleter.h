#pragma once
#include <boost\regex.hpp>
#include "DateFormats.h"
#include <iostream>
#include <fstream>
//#include "indri/UnparsedDocument.hpp"

class FileCompleter
{
public:
	FileCompleter();
	~FileCompleter();
	void doReplace(const std::string fileName, DateFormats* dateFormats);
	std::string doTransformation(const std::string& inputString, DateFormats* dateFormats);
//	indri::parse::UnparsedDocument* doTransformation(indri::parse::UnparsedDocument* document, DateFormats* df);

private:
	void writeFile(std::string outFilePath, const std::string& outString);
	std::string parseFile(std::string fileName);
	std::string replaceDate(std::string inputString, std::string regexp);
};
