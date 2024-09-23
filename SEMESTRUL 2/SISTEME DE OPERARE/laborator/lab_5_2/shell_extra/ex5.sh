#!/bin/bash
if [ $# -eq 0 ]
then 
	echo "nr argv insuficiente"
	echo "mod utilizare: file... cuvant..."
	exit 1
fi 
while true; do
	if [ -z $1 ] || [ -z $2 ]; then
		break
	fi
	if [ ! -f $1 ]; then
		echo " $1 nu e fisier"
		shift 2
		continue
	fi
	nr=$(cat "$1" | grep -E -o "\<$2\>"| wc -l)
	if [ $nr -ge 3 ]
	then
		echo "$2 apare de $nr ori in fisierul $1"
	fi
shift 2
done
exit 0
