#!/bin/bash

if [ $# -eq 0 ]
then 
	echo "nr argv insuf"
	exit 1
fi
if [ ! -d $1 ]
then 
	echo "$1 nu e nume de director valid"
	exit 1
fi
while IFS= read -r fis; do
	if [ ! -e $fis ]; then
		echo "Linkul simbolic $fis pointeaza catre un fisier care nu mai exista"
	fi
done< <(find $1 -type l -print)
exit 0
