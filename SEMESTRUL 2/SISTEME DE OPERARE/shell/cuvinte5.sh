#!/bin/bash

if [ $# -gt 0 ]
then 
	echo "numar insuficient de argumente"
	exit 1
fi 
for fisier in *; do
	if file $fisier| grep -q "ASCII text$"; then
		while read -r  cuv1 t; do
			if [ ! -z "$cuv1" ] && [ "${#cuv1}" -ge 5 ]; then
				echo " in fisierul $fisier apare cuvantul $cuv1 cu lungimea ${#cuv1}"
                                break	
			fi
		done< "$fisier"
	break
	fi
done
exit 0
