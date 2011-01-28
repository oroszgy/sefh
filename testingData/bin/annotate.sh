#!/bin/bash

DIR=`pwd`
LIB="/../lib"
LIBDIR=$DIR$LIB
export LD_LIBRARY_PATH=$LIBDIR 

../../fileAnnotator/Debug/annotateFile $1 $2

