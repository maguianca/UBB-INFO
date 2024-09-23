#!/bin/bash
#8. Să se scrie un script bash care are ca argumente triplete formate dintr-un nume de fisier, un cuvant si un numar k.
# Pentru fiecare astfel de triplet, se vor afişa toate liniile fişierului care contin cuvăntul respectiv exact de k ori.
#(comenzi: shift, wc, sed, grep)

#verific numarul de argumente
if [ $# -eq 0 ]
then
        echo" NUMAR INSUFICIENT DE ARGUMENTE!"
        exit 1
fi

while [ $# -ge 3 ]
do 
	fisier=$1
	cuvant=$2
	numar=$3
	if [ ! -f $fisier ]
	then
		echo"$fisier nu este un fisier valid"
		continue
		shift 3
	fi
	grep -E "\b$cuvant\b" "$fisier" |awk -v k="$numar" -v cuvant="$cuvant" '{count=0; for(i=1;i<=NF;i++){if ($i==cuvant) count++} if(count==k) print }' 

	shift 3
done
exit 0
