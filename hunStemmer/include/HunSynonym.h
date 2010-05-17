#pragma once
#include <string>
#include <stdlib.h>
#include <vector>

namespace com
{
	namespace sefh
	{
		namespace hunstemmer
		{

		class HunSynonym {
		public:
			static HunSynonym* getInstance();
			~HunSynonym();
			std::string processQuery(std::string& word);
			std::vector<std::string> getSyns(std::string& word);
		protected:
			std::string generateSynString(std::string& word);
			HunSynonym();
			static HunSynonym* instance;
		};
		}
	}
}
