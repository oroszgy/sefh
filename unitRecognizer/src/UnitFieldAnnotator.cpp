#include "../include/UnitFieldAnnotator.h"
#include "../include/UnitRecognizer.h"
#include <iostream>

using namespace com::sefh::unitrecognition;

UnitFieldAnnotator::UnitFieldAnnotator(std::string fn) : fieldName(fn)
{
	unitRecognizer = UnitRecognizer::getDefault();
}

UnitFieldAnnotator::~UnitFieldAnnotator(void)
{
	//TODO :fix
//	if(unitRecognizer != NULL)
//		delete unitRecognizer;
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

			try{
			value += unitRecognizer->getSIValue(unit) * 100;
			extent->number = value;
			} catch(...) {
				std::cout<<"Error with: "<<unit<<"\n";
			}
          }
        }
        return document;

}
