#!/bin/bash 

if [ $# -eq 0 ]
then 
	echo "nr argv insuf"
	exit 1
fi 
for x in $*; do
	if [ ! -f $x ];then
		echo "nu e nume de fisier $x"
		continue
	fi
	if file "$x"|grep -q "ASCII text$"; then 
		rezultat=$(sort "$x"| uniq -c | sort -n |tail -n 1|awk '{ print $0}')
		echo "linia cu cele mai multe aparitii in $x este "$rezultat
	fi
done
exit 0
