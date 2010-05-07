#pragma once
#include <string>

namespace com
{
namespace sefh
{
namespace unitrecognition
{
/**
 * Represents a unit.
 */
class Unit
{
public:

	Unit(std::string type_, std::string constant_, double multiplier_);
	/**
	 * The type of the unit. e.g. weight, length...
	 */
	std::string type;
	/**
	 * A string which denotes that the number is a unit. e.g. kg, meter...
	 */
	std::string constant;
	/**
	 * It denotes thta the represented units quotient to the SI unit.
	 *
	 * e.g unit is kg, than multiplier is 1000
	 */
	double multiplier;
};

}
}
}
