#include "../include/FieldAnnotator.h"
#include <boost/regex.hpp>
#include <iostream>
#include <fstream>
#include "DateFormat.h"
#include "UnitRecognizer.h"

using namespace com::sefh::utils;

void FieldAnnotator::doReplace(const std::string fileName, const std::string outputFileName)
{
	/*std::string inputString = StringConverter::WStringToString(
		StringConverter::UTF8ToUnicode(parseFile(fileName)));

	std::string modInputString = StringConverter::UnicodeToUTF8(
		StringConverter::StringToWString(doTransformation(inputString)));*/
	std::string modInputStirng = doTransformation(fileName);

	writeFile(outputFileName, modInputStirng);
}

/*indri::parse::UnparsedDocument* FieldAnnotator::doTransformation(indri::parse::UnparsedDocument* document, DateFormats* df)
{
	std::string content, text;
	content = doTransformation(document->content, df);
	document->contentLength = content.length();
	document->content = content.c_str();
	text = doTransformation(document->text, df);
	document->textLength = text.length();
	document->text = text.c_str();
	return document;
}*/


std::string FieldAnnotator::doDateTransformation(const std::string& inputString)
{
	std::vector<com::sefh::daterecognition::DateFormat>* dates =
		com::sefh::daterecognition::DateFormat::getInstances();
	//std::vector<boost::regex> * dateRegexps = new std::vector<boost::regex>();



	//Create one great regexp...
	std::string dRegexp="(";

	for(size_t i=0; i<dates->size(); ++i)
	{
		dRegexp+="("+dates->at(i).getRecognizerString()+")";
		if(i<dates->size()-1)
			dRegexp+="|";
	}
	dRegexp+=")";

	//annotating
	boost::regex regexp(dRegexp);
	std::string modInputString = boost::regex_replace(inputString, regexp, "<date>$1</date>");

	delete dates;


	return modInputString;
}


std::string FieldAnnotator::doTransformation(const std::string &inputString)
{
	std::string str;
	str = doDateTransformation(parseFile(inputString));
	return doUnitTransformation(str);
}

std::string FieldAnnotator::doUnitTransformation(const std::string& inputString)
{
	std::string input(inputString);

	com::sefh::unitrecognition::UnitRecognizer* ur =
		com::sefh::unitrecognition::UnitRecognizer::getDefault();
	std::map<std::string, std::string>* unitRegExps = ur->getUnitsRecognizingRegexps();
	std::map<std::string, std::string>::iterator it;
	for(it= unitRegExps->begin(); it != unitRegExps->end(); ++it)
	{
		std::string recRegExpStr = "(" + it->second + ")";
		boost::regex unitRegExp(recRegExpStr);
		input = boost::regex_replace(input, unitRegExp, "<" + it->first + ">" + "$1"+
			"</" + it->first + ">");
	}

	return input;
}

std::string FieldAnnotator::parseFile(std::string fileName)
{
	std::string inputFileString;

	std::ifstream* inputFile;
	inputFile = new std::ifstream();
	inputFile->open(fileName.c_str());
	char* line = new char[10240];

	while(!inputFile->eof())
	{
		inputFile->getline(line,10240,'\n');
		inputFileString += line;

		if(!inputFile->eof())
			inputFileString += "\n";
	}
	inputFile->close();
	delete inputFile;

	return inputFileString;
}

void FieldAnnotator::writeFile(std::string outFilePath, const std::string& outString)
{
	std::ofstream* outStream = new std::ofstream();
	outStream->open(outFilePath.c_str());
	(*outStream)<<outString;
	outStream->close();
	delete outStream;
}
