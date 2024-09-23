#!/bin/sh

# Sa se scrie un fisier de comenzi care primeste ca parametri perechi 
# formate dintr-un nume de fisier si un numar n. Pentru fiecare 
# pereche se vor afisa numele fisierului, numarul n si apoi fiecare al 
# n-lea cuvant din fiecare linie din fisier.
if [ $# -eq 0 ]; then
	echo "nr argv incorect"
	echo "utilizare: $1 fisier $2 numar.."
	exit 1
fi
while true; do
	if [ -z $1 ] || [ -z $2 ]; then
		break
	fi
	if [ ! -f $1 ]
	then 
		echo "$1 nu e nume de fis"
		shift 2
		continue
	fi
	if [ $(echo $2| egrep -c "[0-9]+") -eq 0 ]
	then
		echo "$2 nu e nr valid"
		shift 2
		continue
	fi
	while IFS= read -r line; do
		cuvant=$(echo $line| awk -v n=$2 '{if(NF>=n) print $n}')
		echo " al $2-lea cuvant este $cuvant"
	done<$1
shift 2
done
exit 0
