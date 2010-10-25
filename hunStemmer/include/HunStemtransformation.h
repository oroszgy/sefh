#pragma once
#include "lemur/lemur-platform.h"
#include "indri/greedy_vector"
#include "indri/Transformation.hpp"
#include "indri/TermExtent.hpp"
#include "indri/TagExtent.hpp"
#include "indri/ParsedDocument.hpp"


namespace com
{
	namespace sefh
	{
		namespace hunstemmer
		{

		/**
		 * Hungarian stemming implementation of the Indri transformation abstract class
		 */
		class HunStemtransformation :
			public indri::parse::Transformation
		{
		public:
			HunStemtransformation();
			~HunStemtransformation();
			indri::api::ParsedDocument* transform( indri::api::ParsedDocument* document );
		    void handle( indri::api::ParsedDocument* document );
			void setHandler( indri::parse::ObjectHandler<indri::api::ParsedDocument>& handler );
			static void printDbg(indri::api::ParsedDocument* doc);

		private:
			indri::parse::ObjectHandler<indri::api::ParsedDocument>* _handler;
		};
		}
	}
}
