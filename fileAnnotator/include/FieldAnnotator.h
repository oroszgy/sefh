#pragma once
#include <string>

namespace com
{
namespace sefh
{
namespace utils
{
	class FieldAnnotator
	{
	public:
		static void doReplace(const std::string fileName);
		static std::string doTransformation(const std::string& inputString);
		static std::string doDateTransformation(const std::string& inputString);
		static std::string doUnitTransformation(const std::string& inputString);
		// static indri::parse::UnparsedDocument* doTransformation(indri::parse::UnparsedDocument* document, DateFormats* df);

	private:
		FieldAnnotator();
		static void writeFile(std::string outFilePath, const std::string& outString);
		static std::string parseFile(std::string fileName);
	};

}
}
}
