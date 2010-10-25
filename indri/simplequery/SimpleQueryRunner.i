%module libsimplequery
%include "std_string.i"
%include "std_vector.i"

%{
 /* Includes the header in the wrapper code */
 #include "SimpleQueryResult.h"
 #include "SimpleQueryRunner.h"
 %}
 
using namespace std;

namespace std {
   %template(StrVector) vector<string>;
};
 
 /* Parse the header file to generate wrappers */
 %include "SimpleQueryResult.h"
 %include "SimpleQueryRunner.h"
 