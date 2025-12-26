#!/bin/bash
#7. Să se scrie un script bash care primește ca argumente oricâte nume de fișiere.
# Scriptul va citi de la tastatură două cuvinte și va înlocui TOATE aparițiile 
#primului cuvânt cu cel de-al doilea în fiecare fișier furnizat ca argument.
#(comenzi: read, sed)

#verific numarul de argumente
if [ $# -eq 0 ]
then
        echo" NUMAR INSUFICIENT DE ARGUMENTE!"
        exit 1
fi
read -p "Introdu cuvantul căutat: " cuvant
read -p "Introdu cuvantul cu care sa se inlocuiasca: " inlocuire
for NUME in $*
do
        if [ ! -f $NUME ]
        then
                echo"Nu este un fisier valid fisierul cu numele: $NUME"
                continue
        fi
        sed -i "s/$cuvant/$inlocuire/g" "$NUME"
done
exit 0
