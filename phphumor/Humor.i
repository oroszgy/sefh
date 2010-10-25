%module example
%include "std_string.i"
%include "std_vector.i"

%{
 /* Includes the header in the wrapper code */
 
 #include "Humor.h"
 %}
 
using namespace std;

namespace std {
   %template(StringVector) vector<string>;
};
 
 /* Parse the header file to generate wrappers */
 %include "Humor.h"