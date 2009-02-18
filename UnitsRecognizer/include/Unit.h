#pragma once
#include <string>

class Unit
{
public:

	Unit(std::string type_, std::string constant_, double multiplier_);

	std::string type;

	std::string constant;

	double multiplier;
};