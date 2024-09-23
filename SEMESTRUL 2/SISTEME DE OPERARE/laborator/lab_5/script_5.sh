#!/bin/bash

#Să se scrie un script bash care pentru fiecare argument din linia de comandă:
#- dacă e fișier, va afişa numele, numărul de caractere și de linii (în această ordine)
#- dacă e director, va afişa numele și câte fișiere conține (inclusiv în subdirectoare).
#(comenzi: find, grep, test, wc)


#verific numarul de argumente
if [ $# -eq 0 ]
then
        echo" NUMAR INSUFICIENT DE ARGUMENTE!"
        exit 1
fi

for NUME in $*
do 
	if [ -f $NUME ]
	then 
		echo Fisier: $NUME
		NL=$(cat $NUME| wc -l)
		echo Numar linii: $NL
		NC=$(cat $NUME| wc -c)
		echo Numar caractere: $NC
	elif [ -d $NUME ];then
		echo Director: $NUME
		NUM_FILES=$(find "$NUME" -type f | wc -l)
		echo Numar Fisiere:$NUM_FILES
	else 
		echo "Argumentul \"$NUME\" nu este nici fisier, nici director."

	fi 
done
exit 0
