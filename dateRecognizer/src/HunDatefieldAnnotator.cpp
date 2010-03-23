#include "../include/HunDatefieldAnnotator.h"
#include "../include/DateFormat.h"
#include <iostream>
#include "lemur/lemur-platform.h"
#include <boost/regex.hpp>

using namespace com::sefh::daterecognition;

HunDatefieldAnnotator::HunDatefieldAnnotator(std::string field) :
_field(field)  {
	_dateFormats = NULL;
	_dateFormats = DateFormat::getInstances();
}

HunDatefieldAnnotator::~HunDatefieldAnnotator(void)
{
	if(_dateFormats != NULL)
		delete _dateFormats;
}

void HunDatefieldAnnotator::setHandler(indri::parse::ObjectHandler<indri::api::ParsedDocument> &handler)
{
	_handler = &handler;
}

void HunDatefieldAnnotator::handle(indri::api::ParsedDocument *document)
{
	_handler->handle( transform ( document ) );
}

indri::api::ParsedDocument*  HunDatefieldAnnotator::transform(indri::api::ParsedDocument *document)
{
	for( size_t i=0; i<document->tags.size(); i++ ) {
		indri::parse::TagExtent * extent = document->tags[i];
          // reparse from the document text
          if( _field == extent->name ) {
            int dateStart = document->positions[extent->begin].begin;
            int dateEnd = document->positions[extent->end-1].end;

			std::string text(document->text);
			int dateLen = findExtentEnd(dateEnd, text) - dateStart ;
            std::string date;

			date = text.substr(dateStart, dateLen);

			date = cleanup(date);

			//Debug
			std::cout<<date<<std::endl;

            _parseDate(date, extent);

            //Debug
            std::cout<<extent->number<<std::endl;
          }
        }
        return document;
}

std::string HunDatefieldAnnotator::cleanup(std::string& str) {
	boost::regex regexp("<.*?>");
	boost::regex nl("(\\s)+");
	std::string cleanStr = boost::regex_replace(str, regexp, "", boost::match_nosubs);
	return boost::regex_replace(cleanStr, nl, " ");

}

int HunDatefieldAnnotator::findExtentEnd(int supposedEnd, std::string text)
{
	while(text[supposedEnd] != '<')
		++supposedEnd;
	return supposedEnd;
}

//P: Exists a parser which can recognize
void HunDatefieldAnnotator::_parseDate(const std::string& _date, indri::parse::TagExtent *extent) const
{
	std::string day, month, year;

	DateFormat* matchingDateFormat = NULL;
	for(size_t i=0; i<_dateFormats->size(); ++i)
	{
		if(boost::regex_match(_date, boost::regex(_dateFormats->at(i).getSimpleRecognizerString())))
		{
			matchingDateFormat = &(_dateFormats->at(i));
			break;
		}
	}

	//TODO: remove it in the release
	// if there is no matching date format skip
	if(matchingDateFormat == NULL) {
		//Debug
		std::cout<<"No matching date found!\n";
		return;
	}


	month = matchingDateFormat->getMonthIntegerString(_date);
	year = matchingDateFormat->getYear(_date);
	day = matchingDateFormat->getDay(_date);

	std::cout<<year<<month<<day<<std::endl;

	extent->number = indri::parse::DateParse::convertDate(year, month, day);
}
