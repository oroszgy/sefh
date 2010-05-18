#include "Humor.h"
#include "../utils/include/path.h"

using namespace com::weblib::linguist;

Humor::Humor() {
	std::string dir(LEX);
	com::weblib::linguist::HumorCPP::initialize(dir);
}

Humor::Humor(std::string dir) {
	com::weblib::linguist::HumorCPP::initialize(dir);
}

Humor::~Humor() {
	HumorCPP::close();
}

std::string Humor::getClassName() {
	return "Humor (" + HumorCPP::getInitString() + ")";
}

std::vector<std::string> Humor::getSyns(std::string word) {
	if(/*HumorCPP::isInitialized()*/ true) {
		return HumorCPP::getSyns(word);
	}
	std::vector<std::string> ret;
	return ret;
}
