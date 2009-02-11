#pragma once
#include "indri/Transformation.hpp"
#include "indri/DateParse.hpp"
#include "DateFormats.h"
#include "StringCoverter.h"


class HunDatefieldAnnotator :
	public indri::parse::Transformation
{
public:
	HunDatefieldAnnotator(std::string& field, DateFormats* dateFormats);
	~HunDatefieldAnnotator(void);

	indri::api::ParsedDocument* transform( indri::api::ParsedDocument* document );
    void handle( indri::api::ParsedDocument* document );
	void setHandler( indri::parse::ObjectHandler<indri::api::ParsedDocument>& handler );
private:
	indri::parse::ObjectHandler<indri::api::ParsedDocument>* _handler;
	std::string& _field;
	DateFormats* _dateFormats;

	void _parseDate(const std::string& date, indri::parse::TagExtent *extent) const;
};

