#! /bin/bash
  
DIR=`pwd`
LIB="/../lib"
LIBDIR=$DIR$LIB
PAR="/buildIndex.xml"

export LD_LIBRARY_PATH=$LIBDIR 

./runquery runQuery.xml


