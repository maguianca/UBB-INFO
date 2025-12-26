#!/bin/bash

if [ $# -eq 0 ]
then 
	echo "nr argumente insuf"
	echo "mod utilizare: $1 fisier_comenzi $2 fisier_propozitii"
	exit 1
fi
if [ ! -f $1 ] || [ ! -f $2 ]
then 
	echo "$1 nu este un fisier"
	exit 1
fi
fisier_output=$2
while IFS= read -r linie; do
	comenzi=$(echo $linie| awk '{print $1,$2}')
	if [[ "$comenzi" == "REPLACE WORD" ]]
	then 	
			cuv1=$(echo $linie| awk '{print $3}')
			cuv2=$(echo $linie| awk '{print $4}')
			sed -i 's/'$cuv1'/'$cuv2'/g' $fisier_output
	elif [[ "$comenzi" == "APPEND LINE" ]]
	then 
		l=$(echo $linie| awk '{print $3}')
		sed -i '$a '$l'' "$2"
	elif [[ "$comenzi" == "INSERT LINE" ]]
	then 
		nr=$(echo $linie| awk '{print $3}')
		 l=$(echo $linie| awk '{print $4}')
		sed -i ''$nr'i '$l'' "$2"
	fi
done < "$1"
exit 0
