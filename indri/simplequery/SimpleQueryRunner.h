/*
 * SimpleQueryRunner.h
 *
 *  Created on: 2010.09.30.
 *      Author: mee
 */

#pragma once
#include <vector>
#include <string>
#include "SimpleQueryResult.h"

class SimpleQueryRunner {
public:
	SimpleQueryRunner(std::string _indexPath);
	~SimpleQueryRunner();
    std::vector<SimpleQueryResult> runAnnotatedQuery( const std::string& query, int resultsRequested);


private:
    	std::string indexPath;
//    std::vector<indri::utility::greedy_vector<indri::parse::MetadataPair> > getMetaData(std::vector<indri::api::ParsedDocument*>& documents);
//    indri::api::QueryAnnotation* queryAnnotation;
//    indri::api::QueryEnvironment* queryEnvironment;
//    const std::vector<indri::api::ScoredExtentResult>* results;
//    std::vector<indri::api::ParsedDocument*> documents;

};


