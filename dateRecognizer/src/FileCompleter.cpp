#include "..\include\FileCompleter.h"
#include <boost/regex.hpp>

FileCompleter::FileCompleter()
{
}

FileCompleter::~FileCompleter()
{
}

void FileCompleter::doReplace(const std::string fileName, DateFormats* dateFormats)
{
	std::string inputString = parseFile(fileName);

	std::string modInputString = doTransformation(inputString, dateFormats);
	
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


std::string FileCompleter::doTransformation(const std::string& inputString, DateFormats* dateFormats)
{
	std::vector<DateFormat>* dates = dateFormats->getDateFormats();
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
	return "";
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