#! /bin/bash
  
DIR=`pwd`
LIB="/../lib"
LIBDIR=$DIR$LIB
PAR="/indrid.xml"

export LD_LIBRARY_PATH=$LIBDIR
#echo $LD_LIBRARY_PATH

./indrid $DIR$PAR
