#pragma once
#include <indri/greedy_vector>
#include "indri/Transformation.hpp"
#include "indri/TermExtent.hpp"
#include "indri/TagExtent.hpp";
#include "MorphTools.h"

class HunStemtransformation :
	public indri::parse::Transformation
{
public:
	HunStemtransformation();
	~HunStemtransformation();
	indri::api::ParsedDocument* transform( indri::api::ParsedDocument* document );
    void handle( indri::api::ParsedDocument* document );
	void setHandler( indri::parse::ObjectHandler<indri::api::ParsedDocument>& handler );

private:
	MorphTools* morphTools;
	indri::parse::ObjectHandler<indri::api::ParsedDocument>* _handler;
};
