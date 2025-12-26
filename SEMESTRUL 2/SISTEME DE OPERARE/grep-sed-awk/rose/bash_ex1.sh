#!/bin/bash
if [ $# -eq 0 ]
then
	echo "numar insuficient de argumente !"
	echo "Utilizare: $0 fisier"
	exit 1
fi
I=0
LINII=()
while IFS= read -r LINIE
do 
	LINII[I]="$LINIE"
	I=$(($I+1))
done <$1
for((J=I-1;J>=0;J--))
do 
	echo ${LINII[J]}
done
exit 0
