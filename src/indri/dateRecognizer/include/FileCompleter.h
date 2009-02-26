#pragma once
#include <boost\regex.hpp>
#include <iostream>
#include <fstream>
#include "DateFormat.h"

class FileCompleter
{
public:
	FileCompleter();
	~FileCompleter();
	void doReplace(const std::string fileName);
	std::string doTransformation(const std::string& inputString);
	std::string doDateTransformation(const std::string& inputString);
	std::string doUnitTransformation(const std::string& inputString);
//	indri::parse::UnparsedDocument* doTransformation(indri::parse::UnparsedDocument* document, DateFormats* df);

private:
	void writeFile(std::string outFilePath, const std::string& outString);
	std::string parseFile(std::string fileName);
	std::string replaceDate(std::string inputString, std::string regexp);
};
