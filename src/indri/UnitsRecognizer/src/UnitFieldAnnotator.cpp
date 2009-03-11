#include "..\include\UnitFieldAnnotator.h"

UnitFieldAnnotator::UnitFieldAnnotator(std::string fn) : fieldName(fn)
{
	unitRecognizer = UnitRecognizerFactory::getDefault();
}

UnitFieldAnnotator::~UnitFieldAnnotator(void)
{
	if(unitRecognizer != NULL)
		delete unitRecognizer;
}

void UnitFieldAnnotator::setHandler(indri::parse::ObjectHandler<indri::api::ParsedDocument> &handler)
{
	_handler = &handler;
}

void UnitFieldAnnotator::handle(indri::api::ParsedDocument *document)
{
	_handler->handle( transform ( document ) );
}

indri::api::ParsedDocument* UnitFieldAnnotator::transform( indri::api::ParsedDocument* document )
{
	std::string text(document->text);

	for( size_t i=0; i<document->tags.size(); i++ ) {
		indri::parse::TagExtent * extent = document->tags[i];
          // reparse from the document text
		std::string extentName(extent->name);
		if( extentName == fieldName ) {
            int start = document->positions[extent->begin].begin; 
            int end = document->positions[extent->end-1].end;
			int len = end-start;
			std::string unit = text.substr(start, len);

			//double -> integer 2 tizedesig pontos
			UINT64 value = 0;
			
			std::wstring wunit = StringConverter::UTF8ToUnicode(unit);
			std::string _unit = StringConverter::WStringToString(wunit);
			value += unitRecognizer->getSIValue(_unit) * 100;
			extent->number = value;
          }
        }
        return document;

}