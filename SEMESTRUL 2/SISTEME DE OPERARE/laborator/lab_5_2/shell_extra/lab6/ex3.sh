#!/bin/bash
if [ $# -eq 0 ]
then
	echo "nr argv invalid"
	exit 1
fi
if [ ! -f $1 ]
then 
	echo "$1 nu e nume de fisier"
	exit 1
fi
LITERE=$(grep -io '[a-z]' $1|wc -l)
VOCALE=$(grep -io '[aeiou]' $1 |wc -l)
CONSOANE=$(($LITERE-$VOCALE))
echo "Fisierul $1 contine $VOCALE vocale si $CONSOANE consoane."
exit 0

