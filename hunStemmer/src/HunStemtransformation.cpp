#include "../include/HunStemtransformation.h"
#include <iostream>
#include <vector>
#include "HumorCPP.h"


using namespace com::sefh::hunstemmer;

HunStemtransformation::HunStemtransformation()
{
	//TODO: config fájlba egy bejegyzés
	com::weblib::linguist::HumorCPP::initialize("./lex");
}

HunStemtransformation::~HunStemtransformation()
{
	com::weblib::linguist::HumorCPP::close();
}

indri::api::ParsedDocument* HunStemtransformation::transform( indri::api::ParsedDocument* document )
{

	//printDbg(document);
	//indri::utility::greedy_vector<char*>* stems = new indri::utility::greedy_vector<char*>();
	//indri::utility::greedy_vector<indri::parse::TermExtent>* stemPos = new indri::utility::
	//	greedy_vector<indri::parse::TermExtent>();

	indri::utility::greedy_vector<char*>& terms = document->terms;
	for( size_t i=0; i<terms.size(); i++)
	{
		char* term = terms[i];
		//if the term is empty do nothing
		//TODO:: biztos jó ez így?

		if(!term)
			continue;
		std::string input(term);
		if(!(atoi(term) == 0 && input != "0") || input == "")
		{
			continue;
		}
		//std::cout<<input;

		std::vector<std::string>  v =
			com::weblib::linguist::HumorCPP::getStem(input);

		if(v.size() == 0)
			continue;
		// if there is no stem, or the term is a number
		//stems->push_back(term);
		/*if(document->positions.size()>i)
			stemPos->push_back(document->positions[i]);*/


		const char * _t = v[0].c_str();
		char* tt = new char[100];
		strcpy(tt, _t);

		document->terms[i] = tt;


		//add all the stems to the index
	/*	for(int j=0; j< v->size(); ++j)
		{
			std::string _term = v->at(j);
			const char * _t = _term.c_str();
			char* tt = new char[100];
			strcpy(tt, _t);


			stems->push_back(tt);

			if(document->positions.size()>i)
			{
				indri::parse::TermExtent tmpTermExtent;
				tmpTermExtent.begin=document->positions[i].begin;
				tmpTermExtent.end=document->positions[i].end;
				stemPos->push_back(tmpTermExtent);
			}
		}*/

	}

/*	document->terms = *stems;
	document->positions = *stemPos;*/

	//printDbg(document);

	return document;
}

void HunStemtransformation::printDbg(indri::api::ParsedDocument* doc)
{
	std::cout<<"Terms:\n";
	for(int i=0; i<doc->terms.size(); ++i)
		std::cout<<doc->terms[i]<<std::endl;
	std::cout<<"Positions:\n";
	for(int i=0; i<doc->positions.size(); ++i)
		std::cout<<doc->positions[i].begin<<"\t"<<doc->positions[i].end<<std::endl;
	std::cout<<"Tags:\n";
	for(int i=0; i<doc->tags.size(); ++i)
			std::cout<<doc->tags[i]<<std::endl;
	for(int i=0; i<doc->metadata.size(); ++i)
		std::cout<<doc->metadata[i].key<<std::endl;
}

void HunStemtransformation::handle( indri::api::ParsedDocument* document )
{
	_handler->handle( transform( document ) );
}

void HunStemtransformation::setHandler( indri::parse::ObjectHandler<indri::api::ParsedDocument>& handler )
{
	_handler = &handler;
}
