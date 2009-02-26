#include "..\include\FileCompleter.h"
#include <boost/regex.hpp>
#include "UnitRecognizerFactory.h"

FileCompleter::FileCompleter()
{
}

FileCompleter::~FileCompleter()
{
}

void FileCompleter::doReplace(const std::string fileName)
{
	std::string inputString = parseFile(fileName);

	std::string modInputString = doTransformation(inputString);
	
	writeFile(fileName, modInputString);
}

/*indri::parse::UnparsedDocument* FileCompleter::doTransformation(indri::parse::UnparsedDocument* document, DateFormats* df)
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


std::string FileCompleter::doDateTransformation(const std::string& inputString)
{
	std::vector<DateFormat>* dates = DateFormat::getInstances();
	//std::vector<boost::regex> * dateRegexps = new std::vector<boost::regex>();
	
	

	//Create one great regexp...
	std::string dRegexp="(";
	
	for(int i=0; i<dates->size(); ++i)
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


std::string FileCompleter::doTransformation(const std::string &inputString)
{
	std::string str;
	str = doDateTransformation(inputString);
	return doUnitTransformation(str);
}

std::string FileCompleter::doUnitTransformation(const std::string& inputString)
{
	std::string input(inputString);

	UnitRecognizer* ur = UnitRecognizerFactory::getDefault();
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

std::string FileCompleter::parseFile(std::string fileName)
{ 
	std::string inputFileString;

	std::ifstream* inputFile;
	inputFile = new std::ifstream();
	inputFile->open(fileName.c_str());
	char* line = new char[1024];
	
	while(!inputFile->eof())
	{
		inputFile->getline(line,1024,'\n');
		inputFileString += line;

		if(!inputFile->eof())
			inputFileString += "\n";
	}
	inputFile->close();
	delete inputFile;

	return inputFileString;
}

void FileCompleter::writeFile(std::string outFilePath, const std::string& outString)
{
	std::ofstream* outStream = new std::ofstream();
	outStream->open(outFilePath.c_str());
	(*outStream)<<outString;
	outStream->close();
	delete outStream;
}

std::string FileCompleter::replaceDate(std::string inputString, std::string regexp)
{
	return "";
}