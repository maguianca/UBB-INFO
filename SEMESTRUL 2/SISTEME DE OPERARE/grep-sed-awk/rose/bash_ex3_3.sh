#!/bin/bash
if [ $# -eq 0 ]
then
        echo "numar insuficient de argumente !"
        echo "Utilizare: $0 fisier"
        exit 1
fi
LITERE=$(grep -io '[a-z]' $1 | wc -l)
VOCALE=$(grep -io '[aeiou]' $1 | wc -l)
CONSOANE=$(($LITERE-$VOCALE))
echo "Fisierul $1 contine $VOCALE vocale si $CONSOANE consoane."
exit 0
