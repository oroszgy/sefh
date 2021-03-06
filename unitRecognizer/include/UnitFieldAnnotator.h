#pragma once
#include "indri/Transformation.hpp"
#include "UnitRecognizer.h"

namespace com
{
namespace sefh
{
namespace unitrecognition
{
/**
 * Implementation of the indri::parse:Transformation for recognizing units.
 */
class UnitFieldAnnotator :
	public indri::parse::Transformation
{
public:
	UnitFieldAnnotator(std::string fn);
	~UnitFieldAnnotator(void);
	indri::api::ParsedDocument* transform( indri::api::ParsedDocument* document );
    void handle( indri::api::ParsedDocument* document );
	void setHandler( indri::parse::ObjectHandler<indri::api::ParsedDocument>& handler );
private:
	indri::parse::ObjectHandler<indri::api::ParsedDocument>* _handler;

	UnitRecognizer* unitRecognizer;
	std::string fieldName;
};
}
}
}
