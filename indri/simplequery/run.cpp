/*
 * test.cpp
 *
 *  Created on: 2010.10.05.
 *      Author: mee
 */

#include "SimpleQueryRunner.h"
#include <string>
#include <iostream>
#include <stdlib.h>
#include "lemur/Exception.hpp"

#define HEADER std::string("<?xml version=\"1.0\"?>")
#define RES_S std::string("<result>")
#define RES_E std::string("</result>")
#define TYPE_S std::string("<type>")
#define TYPE_E std::string("</type>")
#define REASON_S std::string("<reason>")
#define REASON_E std::string("</reason>")
#define DATA_S std::string("<data>")
#define DATA_E std::string("</data>")
#define OK std::string("ok")
#define ERROR std::string("error")

std::string buildErrorResult(std::string msg) {
	return HEADER + RES_S + TYPE_S + ERROR + TYPE_E + REASON_S + msg + REASON_E + RES_E;
}

std::string buildResult(std::vector<SimpleQueryResult>& r) {
	std::string before = HEADER + RES_S + TYPE_S + OK + TYPE_E + DATA_S;
	std::string after = DATA_E + RES_E;
	std::string result = before;
	for(int i=0; i<r.size(); ++i) {
		result += r[i].toXML();
	}
	result += after;
	return result;
}

//Parameters: index, query, numberOfResults
int main(int argc, char** argv) {
	if(argc<4)
	{
		std:cout<<buildErrorResult("Not enough parameters!");
		return -1;
	}
	std::string indexPath, query, resultsNumber;
	indexPath = argv[1];
	query = argv[2];
	resultsNumber = argv[3];
	int numberOfResults = atoi(resultsNumber.c_str());
	try {
		SimpleQueryRunner qr(indexPath);
		std::vector<SimpleQueryResult> r = qr.runAnnotatedQuery(query, numberOfResults);
		std::cout<<buildResult(r);
	} catch( lemur::api::Exception e) {
		std::cout<<buildErrorResult(std::string(e.what()));
		return -2;
	}
	std::cout<<endl;
	return 0;
}
