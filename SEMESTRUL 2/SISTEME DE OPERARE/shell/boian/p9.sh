#!/bin/bash
if [ $# -eq 0 ]
then 
	echo "Numar insuficient de argumente" 
	exit 1
fi 
if [ ! -d $1 ]
then 
	echo "Error: $1 nu este un director valid "
	exit 1

fi 
declare -A checksums
find $1 -type f -print0|sort -z |while IFS= read -r -d '' file; do
	checksum=$(md5sum $file |awk '{print$1}')
	if [ -n "${checksums[$checksum]}" ]; then 
		echo "Duplicate: $file"
		echo "         :${checksums[$checksum]}"
	else
		checksums[$checksum]="$file"
	fi
done
exit 0
