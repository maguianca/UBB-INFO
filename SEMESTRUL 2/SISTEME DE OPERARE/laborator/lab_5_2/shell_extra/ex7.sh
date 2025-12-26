#!/bin/bash
if [ $# -eq 0 ]
then 
	echo "nr argv insuficiente"
	echo "mod utilizare: fisier:.."
	exit 1
fi
if [ ! -d $1 ]
then 
	echo "$1 nu este nume de director valid"
	exit 1
fi


find $1 -type f -print|awk -F/ '{print $NF}'|sort|uniq -c

