/*
 * SimpleQueryRunner.cpp
 *
 *  Created on: 2010.09.30.
 *      Author: György Orosz
 */

#include "SimpleQueryRunner.h"
#include "indri/QueryEnvironment.hpp"
#include "indri/SnippetBuilder.hpp"
#include "indri/ScoredExtentResult.hpp"
#include "indri/CompressedCollection.hpp"
#include "indri/Repository.hpp"


SimpleQueryRunner::SimpleQueryRunner(std::string _indexPath) {
	indexPath = _indexPath;
}

SimpleQueryRunner::~SimpleQueryRunner() {
}


/*std::vector<indri::utility::greedy_vector<indri::parse::MetadataPair> > SimpleQueryRunner::getMetaData(std::vector<indri::api::ParsedDocument*>& documents) {
	std::vector<indri::utility::greedy_vector<indri::parse::MetadataPair> > result;
	for(int i=0; i<documents.size(); ++i) {
		result.push_back(documents[i]->metadata);
	}
	return result;
}*/

std::vector<SimpleQueryResult> SimpleQueryRunner::runAnnotatedQuery( const std::string& query, int resultsRequested) {
	indri::collection::Repository* repository = new indri::collection::Repository();
	repository->openRead(indexPath);
	indri::api::QueryEnvironment* queryEnvironment = new indri::api::QueryEnvironment();
	queryEnvironment->addIndex(indexPath);
	indri::api::QueryAnnotation* queryAnnotation = queryEnvironment->runAnnotatedQuery(query, resultsRequested);
	const std::vector<indri::api::ScoredExtentResult>* results = &(queryAnnotation->getResults());

	indri::api::SnippetBuilder* builder = new indri::api::SnippetBuilder(true);
		std::vector<std::string> snippets;// = new std::vector<std::string>();
		std::vector<indri::api::ParsedDocument*> documents = queryEnvironment->documents(*results);
		for(int i=0; i<results->size(); ++i) {
			indri::api::ScoredExtentResult ser = results->at(i);
			std::string snippet = builder->build(ser.document,documents[i],queryAnnotation);
			snippets.push_back(snippet);
		}

	std::vector<SimpleQueryResult> ret;

	for(int i=0; i<snippets.size(); ++i) {
		SimpleQueryResult res;
		res.snippet = snippets[i];
		/*for(int j=0; j<documents[i]->metadata.size(); ++j) {
			std::cout<<(std::string)documents[i]->metadata.at(j).key;
		}*/
		indri::utility::greedy_vector<indri::parse::MetadataPair>::iterator iter = std::find_if( documents[i]->metadata.begin(),
		                                                                                                 documents[i]->metadata.end(),
		                                                                                                 indri::parse::MetadataPair::key_equal( "docno" ) );
		lemur::api::DOCID_T docno;
		if( iter != documents[i]->metadata.end() ) {
		     res.path = std::string((char *) iter->value);
		     //docno = (lemur::api::DOCID_T)iter->value;
		}
		/*iter = std::find_if( documents[i]->metadata.begin(), documents[i]->metadata.end(),indri::parse::MetadataPair::key_equal( "path" ) );
		if( iter != documents[i]->metadata.end() )
		     res.path = (char*) iter->value;*/

		iter = std::find_if( documents[i]->metadata.begin(),documents[i]->metadata.end(),indri::parse::MetadataPair::key_equal( "url" ) );
		if( iter != documents[i]->metadata.end() )
		     res.url = (char*) iter->value;

		 iter = std::find_if( documents[i]->metadata.begin(),documents[i]->metadata.end(),indri::parse::MetadataPair::key_equal( "title" ) );
		if( iter != documents[i]->metadata.end() )
		     res.title = (char*) iter->value;

		//std::cout << "most:" << repository->collection()->retrieveMetadatum(docno, "docno") << "eddig";
		/*  for( size_t i=0; i<documents[i]->metadata.size(); i++ ) {
		    if( documents[i]->metadata[i].key[0] == '#' )
		      continue;

		    std::cout << documents[i]->metadata[i].key << ": "
		              << (const char*) documents[i]->metadata[i].value
		              << std::endl;
		  }*/
		ret.push_back(res);
	}

	delete builder;
	delete queryAnnotation;
	delete queryEnvironment;
	delete repository;
	for(int i=0; i<documents.size(); ++i) {
		indri::api::ParsedDocument* tmp = documents[i];
		delete tmp;
	}
	return ret;

}

