#!/bin/bash
#6. Să se scrie un script bash care primește ca argumente oricâte nume de fișiere. 
#Scriptul va citi de la tastatură un cuvânt, va determina și afișa numărul de apariţii ale 
#cuvântului în fiecare fișier furnizat ca argument.
#(comenzi: read, grep)

#verific numarul de argumente
if [ $# -eq 0 ]
then
        echo" NUMAR INSUFICIENT DE ARGUMENTE!"
        exit 1
fi
read -p "Introdu cuvântul căutat: " cuvant
for NUME in $*
do
	if [ ! -f $NUME ]
	then
		echo"Nu este un fisier valid fisierul cu numele: $NUME"
		continue
	fi	
	rezultat=$(cat $NUME| grep -o -w "$cuvant" | wc -l)
	echo "Numărul de apariții ale cuvântului $cuvant în fisierul $NUME este: $rezultat"
done
exit 0
