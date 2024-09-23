#!/bin/bash 
if [ $# -eq 0 ]; then 
	echo "nr parametrii invalid"
	echo "utilizare: $0 nume fisier"
	exit 1
fi
suma=0
total=0
while IFS= read -r linie; do
	for cuvant in $linie; do
		if [[ $cuvant =~ ^[0-9]+$ ]]; then 
			suma=$(($suma+$cuvant))
			total=$(($total+1))
		fi
	done
done< "$1"
echo "suma nr valide este $suma si sunt $total nr valide"
exit 0
