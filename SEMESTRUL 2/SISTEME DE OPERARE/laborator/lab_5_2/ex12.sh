#!/bin/bash 
if [ $# -eq 0 ]
then 
	echo "nr argv insuf"
	exit 1
fi
if [ ! -d $1 ]
then 
	echo "nu este $1 nume de director"
	exit 1
fi 
while IFS= read -r fis; do
	echo "$fis redenumit"
	mv "$fis" "${fis}.all"
done< <(find $1 -type f -perm 222 -print)
exit 0
