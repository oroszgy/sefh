#pragma once
#include "../humor/include/HumorCPP.h"
#include <string>

class Humor {
public:
	Humor();
	Humor(std::string dir);
	~Humor();
	std::vector<std::string> getSyns(std::string word);
	std::string getClassName();
};




