#!/bin/bash
s=0
for f in `find $1 -type f -name "*.c"`; do
	N=`grep "[^ \t]" $f | wc -l`
        s=`expr $s+$N`
done 
echo $s
