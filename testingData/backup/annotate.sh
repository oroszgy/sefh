#!/bin/bash

#L = "$(ls ./ogy/utf8/*.txt)"
for a in ./ogy/utf8/part/*.txt ; do 
	f="$(echo "./ogy/annotated/part/"${a##*/})"
	../fileAnnotator/Debug/annotateFile $a $f
done 
