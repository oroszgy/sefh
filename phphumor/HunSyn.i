%module example
%include "std_string.i"
%include "std_vector.i"

%{
 /* Includes the header in the wrapper code */
 
 #include "../hunStemmer/include/HunSynonym.h"
 %}
 
 /* Parse the header file to generate wrappers */
 %include "../hunStemmer/include/HunSynonym.h"