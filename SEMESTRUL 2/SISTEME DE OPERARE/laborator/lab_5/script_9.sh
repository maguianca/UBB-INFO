#!/bin/bash
#8. Să se scrie un script bash care are ca argumente triplete formate d># Pentru fiecare astfel de triplet, se vor afişa toate liniile fişierul>#(comenzi: shift, wc, sed, grep)

#verific numarul de argumente
if [ $# -eq 0 ]
then
        echo" NUMAR INSUFICIENT DE ARGUMENTE!"
        exit 1
fi

for file in $*
do 
	if [ ! -f $file ]
	then 
		echo "$file nu este un nume de fisier valid"
		exit 1
	fi
	rezultat=$(sort "$file" | uniq -c | sort -n| tail -n 1|  awk '{$1=""; print $0}')
	echo "Linia cu cele mai multe aparitii in fisierul $file este: $rezultat"
done
exit 0

