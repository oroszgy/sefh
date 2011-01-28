#! /bin/bash
  
DIR=`pwd`
LIB="/../lib"
LIBDIR=$DIR$LIB
PAR="/buildIndex.xml"

export LD_LIBRARY_PATH=$LIBDIR 
rm testIndex -r
../../indri/buildindex/buildindex ./buildIndex.xml

rm ../indeces/testIndex -r
mv ./testIndex ../indeces
