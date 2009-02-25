#include "../include/HunStemtransformation.h"
#include "../include/MorphToolsFactory.h"
#include <iostream>
#include "../include/StringCoverter.h"
#include <vector>
#include "ParsedDocument.hpp";



HunStemtransformation::HunStemtransformation()
{
	morphTools = MorphToolsFactory::getDefault();
}

HunStemtransformation::~HunStemtransformation()
{
	// no need to delete morphTools, because it is the only instance
}

indri::api::ParsedDocument* HunStemtransformation::transform( indri::api::ParsedDocument* document )
{

	indri::utility::greedy_vector<char*>* stems = new indri::utility::greedy_vector<char*>();
	indri::utility::greedy_vector<indri::parse::TermExtent>* stemPos = new indri::utility::
		greedy_vector<indri::parse::TermExtent>();

	indri::utility::greedy_vector<char*>& terms = document->terms;

	for( size_t i=0; i<terms.size(); i++)
	{
		char* term = terms[i];
		if(!term || StringConverter::UTF8ToUnicode(term)==L"")
			continue;

		std::vector<std::wstring>*  v = 
			morphTools->getStems(StringConverter::UTF8ToUnicode(term));
		if(v==NULL || !(atoi(term) == 0 && std::string(term) != "0"))
		{
			stems->push_back(term);
			if(document->positions.size()>i)
				stemPos->push_back(document->positions[i]);
			continue;
		}

		for(int j=0; j< v->size(); ++j)
		{
			std::string _term = StringConverter::UnicodeToUTF8(v->at(j));
			const char * _t = _term.c_str();
			char* tt = new char[100];
			strcpy(tt, _t);

	
			stems->push_back(tt);
			if(document->positions.size()>i)
				stemPos->push_back(document->positions[i]);
		}
		
	}
	
	document->terms = *stems;
	document->positions = *stemPos;

	return document;
}

void HunStemtransformation::handle( indri::api::ParsedDocument* document )
{
	_handler->handle( transform( document ) );
}

void HunStemtransformation::setHandler( indri::parse::ObjectHandler<indri::api::ParsedDocument>& handler )
{
	_handler = &handler;
}
