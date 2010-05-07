#/bin/bash

DIR=`pwd`
LIB="/../lib"
LIBDIR=$DIR$LIB
export LD_LIBRARY_PATH=$LIBDIR 

for a in /home/mee/Projects/ogy/xml/2000/annotated/*
do
./annotateFile $a $a
done
