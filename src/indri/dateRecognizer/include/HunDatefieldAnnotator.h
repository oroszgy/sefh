#pragma once
#include "indri/Transformation.hpp"
#include "indri/DateParse.hpp"
#include "DateFormatsContainer.h"
#include "StringCoverter.h"


class HunDatefieldAnnotator :
	public indri::parse::Transformation
{
public:
	HunDatefieldAnnotator(std::string field);
	~HunDatefieldAnnotator(void);

	indri::api::ParsedDocument* transform( indri::api::ParsedDocument* document );
    void handle( indri::api::ParsedDocument* document );
	void setHandler( indri::parse::ObjectHandler<indri::api::ParsedDocument>& handler );
private:
	indri::parse::ObjectHandler<indri::api::ParsedDocument>* _handler;
	int findExtentEnd(int supposedEnd, std::string text);
	std::string _field;
	std::vector<DateFormat>* _dateFormats;

	void _parseDate(const std::string& date, indri::parse::TagExtent *extent) const;
};

