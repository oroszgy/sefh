#include "..\include\HunDatefieldAnnotator.h"
#include "..\include\DateFormat.h"


HunDatefieldAnnotator::HunDatefieldAnnotator(std::string field) :
_field(field)  {
	_dateFormats = DateFormat::getInstances();
}

HunDatefieldAnnotator::~HunDatefieldAnnotator(void)
{
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
            _parseDate(date, extent);
          }
        }
        return document;
}

int HunDatefieldAnnotator::findExtentEnd(int supposedEnd, std::string text)
{
	while(text[supposedEnd] != '<')
		++supposedEnd;
	return supposedEnd;
}

//P: Exists a parser which can recognize
void HunDatefieldAnnotator::_parseDate(const std::string& date, indri::parse::TagExtent *extent) const
{
	std::wstring wdate = StringConverter::UTF8ToUnicode(date);
	std::string _date = StringConverter::WStringToString(wdate);
	std::string day, month, year;

	DateFormat* matchingDateFormat;
	for(int i=0; i<_dateFormats->size(); ++i)
	{
		if(boost::regex_match(_date, _dateFormats->at(i).getRecognizerRegExp()))
		{
			matchingDateFormat = &(_dateFormats->at(i));
			break;
		}
	}

	month = matchingDateFormat->getMonthIntegerString(_date);
	year = matchingDateFormat->getYear(_date);
	day = matchingDateFormat->getDay(_date);

	extent->number = indri::parse::DateParse::convertDate(year, month, day);
}