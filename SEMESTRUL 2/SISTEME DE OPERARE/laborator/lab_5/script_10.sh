#!/bin/bash

#10. Să se scrie un script bash care va afişa toate numele de fişiere dintr-un director dat ca argument 
#şi din subdirectoarele sale, care au numele mai scurte de 8 caractere.
#Pentru acestea, dacă sunt fişiere text, li se vor afişa primele 10 lini
if [ $# -eq 0 ]
then
        echo" NUMAR INSUFICIENT DE ARGUMENTE!"
        exit 1
fi

director=$1
if [ ! -d $director ]
then
     echo "$director nu este un nume de director valid"
     exit 1
fi

find $director -type f| while read -r fisier
do 
	nume=$(basename "$fisier")
	if [ ${#nume} -lt 8 ]
	then 
		if file "$fisier" |grep -q "ASCII text" 
		then
			echo "Nume fisier: " $fisier
			echo "Primele 10 linii"
			head "$fisier"
			echo "---------------------"
		fi
	fi
done
exit 0
