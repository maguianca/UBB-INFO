#!/bin/bash

sum=0
count=0
while [[ $# -ne 0 ]] ; do 
	if (( $1 %8 == 0 ));then
		sum=$((sum + $1))
	fi
	count=$((count+1))
	shift 1
done
echo "$count"
