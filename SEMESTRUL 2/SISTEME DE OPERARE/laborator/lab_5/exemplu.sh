#!/bin/bash
#afiseaza nr de cifre
#verific numarul de argumente
if [ $# -eq 0 ]
then
        echo" NUMAR INSUFICIENT DE ARGUMENTE!"
        echo" Utilizare: $0 N"
        exit 1
fi

read -p "Numar cifre: " NC

FILES=$(find $1 -type f)
for FILE in $FILES
do
        if cat $FILE | grep -qE "[0-9]{$NC,}"
        then
                echo Fisier: $FILE
        fi
done
