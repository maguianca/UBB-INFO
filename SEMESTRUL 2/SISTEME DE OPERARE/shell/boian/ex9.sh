#!/bin/bash

if [ $# -eq 0 ]
then 
	echo "nr argv insuf"
	exit 1
fi
if [ ! -d $1 ]
then 
	echo " $1 nu e director"
	exit 1
fi
declare -A checksum
while IFS= read -r fis; do
	nr=$(md5sum $fis| awk '{print $1}')
	if [ -n "${checksum[$nr]}" ]; then
		echo "Duplicate: $fis"
		echo " 		:${checksum[$nr]}"
	else
		checksum[$nr]="$fis"
	fi
done< <(find $1 -type f -print)
