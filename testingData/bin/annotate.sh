#!/bin/bash

DIR=`pwd`
LIB="/../lib"
LIBDIR=$DIR$LIB
export LD_LIBRARY_PATH=$LIBDIR 

./annotateFile $1 $2

