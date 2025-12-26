#!/bin/bash

if [ $# -eq 0 ]
then 
	echo "nr argv insuf"
	exit 1
fi
if [ ! -d $1 ]
then 
	echo "$1 nu este nume de director valid"
	exit 1
fi
nr=0
for x in $(find $1 -type f -name "*.c"); do 
	nl=$(cat $x| wc -l)
	if [ $nl -gt 500 ]
	then 
		if [ $nr -lt 2 ]
		then 
			nr=$(($nr+1))
			echo "$x"
		else
			break
		fi
	fi
done 
exit 0
