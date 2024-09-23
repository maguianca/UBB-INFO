#!/bin/bash
if [ $# -eq 0 ]
then 
	echo "nr argv invalid"
	exit 1
fi
for fis in $*; do 
	if [ -f $fis ]; then
		echo "Fisier: $fis"
		c=$(cat $fis| wc -c)
		echo "Nr caractere: $c"
		linii=$(cat $fis| wc -l)
		echo "Nr linii: $linii"
	elif [ -d $fis ]; then
		echo "Director: $fis"
		nr=$( find $fis -type f -print| wc -l)
		echo "Nr fisiere/subdirectoare $nr"
	fi
done
exit 0
