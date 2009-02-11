#include "Index.hpp"
#include "IndexManager.hpp"
 
 using namespace lemur::api;
 
 void main(int argc, char *argv[]) {
   // we assume the index path is the first argument
	 char *indexPath="e:\\index\\index_hun";//argv[1];
 
   // open the index
   Index *theIndex=IndexManager::openIndex(indexPath);
 
   // get a the total number of unique terms
   // which will give us our max term ID
   int maxTermID=theIndex->termCountUnique();
 
   // now loop over the terms
   for (int t=1; t <= maxTermID; t++) {
     // get the term as a string
     TERM_T thisTermString=theIndex->term(t);
 
     // get the TF of this term
     int termCount=theIndex->termCount(t);
 
     // get the document count for this term
     int docCount=theIndex->docCount(t);
 
     // print it out
     cout << t << "\t" << thisTermString << "\t";
     cout << termCount << "\t" << docCount << endl;
   }
 
   // finally delete the index (which closes it)
   delete theIndex;
 }
