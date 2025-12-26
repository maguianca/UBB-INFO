#!/bin/bash
if [ $# -eq 0 ] 
then 
	echo "nr argv insuficiente"
	echo "mod utilizare: $1 director"
	exit 1
fi 
if [ ! -d $1 ]
then 
	echo "$1 nu este nume de director"
	exit 1
fi 
while IFS= read -r fis; do
	perm=$(ls -l|awk -v fis=$fis '$NF ==fis {print$1}')
	echo "$perm $nume"
	chmod o-w $fis
	perm=$(ls -l|awk -v fis=$fis '$NF ==fis {print$1}')
 	echo "$perm $nume"
done< <(find $1 -type f -perm o=w)
exit 0
