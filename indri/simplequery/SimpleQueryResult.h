#pragma once
#include <string>

struct SimpleQueryResult {
	std::string snippet;
	std::string title;
	std::string path;
	std::string url;
	std::string docno;

	std::string toString() {
		std::string r = title + "(";
		r+=")\t" + path + "\t" + url + "\n" + snippet + "\n";
		return r;
	}

	std::string toXML() {
		return "<item><title>" + title + "</title>" +
				"<path>" + path + "</path>" +
				"<snippet>" + snippet + "</snippet></item>";
	}

};


