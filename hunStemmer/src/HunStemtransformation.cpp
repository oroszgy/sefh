#include "../include/HunStemtransformation.h"
#include <iostream>
#include <vector>
#include "HumorCPP.h"


using namespace com::sefh::hunstemmer;

HunStemtransformation::HunStemtransformation()
{
	//TODO: config fájlba egy bejegyzés
	com::weblib::linguist::HumorCPP::initialize("./lex", 1038);
}

HunStemtransformation::~HunStemtransformation()
{
	com::weblib::linguist::HumorCPP::close();
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
		//if the term is empty do nothing
		//TODO:: biztos jó ez így?
		if(!term || term=="")
			continue;

		std::vector<std::string>*  v =
			com::weblib::linguist::HumorCPP::getStem(term);
		// if there is no stem, or the term is a number
		if(v==NULL || !(atoi(term) == 0 && std::string(term) != "0"))
		{
			stems->push_back(term);
			if(document->positions.size()>i)
				stemPos->push_back(document->positions[i]);
			continue;
		}

		//add all the stems to the index
		for(int j=0; j< v->size(); ++j)
		{
			std::string _term = v->at(j);
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
