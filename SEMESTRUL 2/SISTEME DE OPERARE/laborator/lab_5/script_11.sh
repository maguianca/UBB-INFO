#!/bin/bash

#11. Să se scrie un script bash care pentru fiecare fişier cu drepturile 755 dintr-un director (şi subdirectoarele sale) 
#dat ca argument îi va modifica drepturile de acces în 744. Înainte de a modifica drepturile 
#de acces, script-ul va cere confirmarea din partea utilizatorului (pentru fiecare fişier în parte).
#(comenzi: find, chmod, read)
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

fisiere=$(find $director -type f -perm 755)
for file in $fisiere
do
	echo"Modificati drepturile de acces pentru $file la 744: Da/Nu"
	read -r raspuns
	if [ $raspuns="Da" ] ||  [ $raspuns="DA" ]|| [ $raspuns="DA" ]
	then 
		chmod 744 "$file"
		echo "Drepturile au fost modificate"
	else 
		echo "Drepturile nu au fost modificate"
	fi
done
exit 0


