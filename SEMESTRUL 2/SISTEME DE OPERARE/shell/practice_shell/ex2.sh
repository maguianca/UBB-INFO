#!/bin/bash

if [ $# -eq 0 ]
then 
	echo "nr argumente insuf"
	echo "mod utilizare: $1 extensie, $2...path-uri"
	exit 1
fi

extensie=$1
shift 1
for x in $*; do
	while IFS= read -r fis; do
		nume_fis=$(basename $fis)
		#nume_fis=$(echo $fis|awk -F'/' '{print $NF}')
		nl=$(cat $fis|wc -l)
		dim=$(ls -l $fis| awk '{print $5}')
		#size=$(du -b $fis| cut -f1)
		#echo "dimenisune: $size"
		#echo "$fis"| sed -n  's/\b$nume_fis\b//'
		echo "$nume_fis (in ./$(dirname $fis)"
		echo "Linii: $nl"
		echo "Dimensiune: $dim"


	done< <(find $x -type f -name "*$extensie")
done
exit 0
