#include "..\include\HunDatefieldAnnotator.h"
#include "..\include\DateFormat.h"


HunDatefieldAnnotator::HunDatefieldAnnotator(std::string& field, DateFormats* dateFormats) :
_field(field)  {
	_dateFormats = dateFormats;
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
			int dateLen = dateEnd - dateStart ;
            std::string date;
			//Converting
			/*std::wstring wtext = StringCoverter::UTF8ToUnicode(document->text);
			std::string text = StringCoverter::WStringToString(wtext);*/
			std::string text(document->text);

			int dateD1 = document->positions[extent->end-1].begin;
			int dateD2 = document->positions[extent->end-1].end;
			int dateM1 = document->positions[extent->end-2].begin;
			int dateM2 = document->positions[extent->end-2].end;
			std::string tmp0 = text.substr(dateStart, dateD1-dateStart);
			std::string tmp1 = text.substr(dateStart, dateD2-dateStart);
			std::string tmp2 = text.substr(dateStart, dateM1-dateStart);
			std::string tmp3 = text.substr(dateStart, dateM2-dateStart);

			date = text.substr(dateStart, dateLen);
            _parseDate(date, extent);
          }
        }
        return document;
}

//P: Exists a parser which can recognize
void HunDatefieldAnnotator::_parseDate(const std::string& date, indri::parse::TagExtent *extent) const
{
	std::wstring wdate = StringCoverter::UTF8ToUnicode(date);
	std::string _date = StringCoverter::WStringToString(wdate);
	std::string day, month, year;
	std::vector<DateFormat>* dfs = _dateFormats->getDateFormats();

	DateFormat* matchingDateFormat;
	for(int i=0; i<dfs->size(); ++i)
	{
		if(boost::regex_match(_date,	dfs->at(i).getRecognizerRegExp()))
		{
			matchingDateFormat = &(dfs->at(i));
			break;
		}
	}

	month = matchingDateFormat->getMonthIntegerString(_date);
	year = matchingDateFormat->getYear(_date);
	day = matchingDateFormat->getDay(_date);

	extent->number = indri::parse::DateParse::convertDate(year, month, day);
}
