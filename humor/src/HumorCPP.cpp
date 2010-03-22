#include "../include/HumorCPP.h"
#include <stdlib.h>
#include <iostream>
#include <exception>
#include <stdio.h>
#include <string.h>
#include <boost/algorithm/string.hpp>


using namespace com::weblib::linguist;

iconv_t com::weblib::linguist::HumorCPP::utc = 0;
iconv_t com::weblib::linguist::HumorCPP::ctu = 0;
int com::weblib::linguist::HumorCPP::morphId = 0;
//not necessary: filter_derived stems
int com::weblib::linguist::HumorCPP::stemOptions = SHOW_STEM_ONLY | FILTER_STEM | FILTER_DERIVED_STEMS;
int com::weblib::linguist::HumorCPP::synOptions = 0;

void HumorCPP::initialize(std::string dir)
{
	ctu = openCpToUtf();
	utc = openUtfToCp();
	morphId = init(dir.c_str(),1038,1250,0);
}

bool HumorCPP::isInitialized()
{
	return ctu != NULL && utc != NULL && morphId >= 0;
}

int HumorCPP::close()
{
	closeDesc(ctu);
	closeDesc(utc);
	ctu = 0; utc = 0;
	::close(morphId);
	morphId = -10;
	return 0;
}

std::vector<std::string> HumorCPP::getStem(std::string word)
{
	char out[512];
	std::string inData = convert(utc,word);
	int ret = stem(morphId, inData.c_str(), out, sizeof(out)/sizeof(out[0]), stemOptions);
	std::string output(out);
	if(ret  == 0) {
		std::string tmp1 = convert(ctu, output);
		return split(tmp1);
	}
	else {
		std::vector<std::string> ret;
		return ret;
	}
}

std::vector<std::string> HumorCPP::getSyns(std::string word)
{
	char out[512];
	std::string inData= std::string(convert(utc,word));
	int ret = get_synonims(morphId, inData.c_str(), out, sizeof(out)/sizeof(out[0]), synOptions);
	if(ret == 0 && std::string(out) != "")
		return split(convert(ctu,out));
	else {
		std::vector<std::string> ret;
		return ret;	}
}

std::vector<std::string> HumorCPP::split(std::string str) {
	std::vector<std::string>* ret = new std::vector<std::string>();
	boost::split(*ret, str, boost::is_any_of(","));
	//for(int i=0; i<ret->size() ;++i)
	//	std::cout << ret->at(i);
	return *ret;
}

iconv_t HumorCPP::openUtfToCp ()
{
    iconv_t conv_desc;
    conv_desc = iconv_open ("CP1250", "UTF-8");
    return conv_desc;
}

iconv_t HumorCPP::openCpToUtf ()
{
    iconv_t conv_desc;
    conv_desc = iconv_open ("UTF-8","CP1250");
    return conv_desc;
}


std::string HumorCPP::convert (iconv_t desc, std::string fromStr)
{
	if( fromStr == "")
		return "";
    size_t iconv_value;
    char * toStr;
    unsigned int fromLen;
    unsigned int toLen;

    //char * toStart;
    //char * fromStart;
    //unsigned int fromStartLen;
    //unsigned int toStartLen;

    fromLen = fromStr.length();

    toLen = 2*fromLen;
    toStr = (char*)calloc (toLen, 1);
    //fromStart = (char*)calloc (toLen, 1);
    char* fromTmpStr;
    fromTmpStr = (char*)calloc (toLen, 1);

    //fromStartLen = fromLen;
    //toStartLen = toLen;

    char* toStart = toStr;
    //strcpy(fromStart,  fromStr.c_str());
    strcpy(fromTmpStr,  fromStr.c_str());
    char * deltmpstr = fromTmpStr;
    /* Display what is in the variables before calling iconv. */
    iconv_value = iconv (desc, & fromTmpStr, & fromLen, & toStr, & toLen);
    /* Handle failures. */
    /*if (iconv_value == (size_t) -1) {
        fprintf (stderr, "iconv failed: in string '%s', length %d, "
                "out string '%s', length %d\n",
                 euc, len, utf8start, utf8len);
        switch (errno) {
        case EILSEQ:
            fprintf (stderr, "Invalid multibyte sequence.\n");
            break;
        case EINVAL:
            fprintf (stderr, "Incomplete multibyte sequence.\n");
            break;
        case E2BIG:
            fprintf (stderr, "No more room.\n");
            break;
        default:
            fprintf (stderr, "Error: %s.\n", strerror (errno));
        }
        exit (1);
    }*/
    /* Display what is in the variables after calling iconv. */
    std::string ret(toStart);
    	free(toStart);
    	free(deltmpstr);

    return ret;
}

void HumorCPP::closeDesc (iconv_t conv_desc)
{
	if(conv_desc != NULL)
		iconv_close(conv_desc);
}
