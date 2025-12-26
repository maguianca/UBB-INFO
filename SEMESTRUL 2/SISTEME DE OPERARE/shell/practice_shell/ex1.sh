#!/bin/bash
if [ $# -eq 0 ]
then 
	echo "nr argumente insuf"
	echo "mod utilizare $1 numar nat"
	exit 1
fi
if ! [[ $1 =~ ^[0-9]+$ ]] 
then 
	echo "$1 nu este numar natural"
	exit 1
fi

for (( i=1;i<=$1;i++))
do
	var=$(date +%-H:%-M:%-S)
	if [[ $var =~ [02468]$ ]]
	then 
		echo "$var tic"
	else
		echo "$var toc"
	fi
	sleep 1
done
exit 0
