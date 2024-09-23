#!/bin/bash
if [ $# -eq 0 ]
then 
	echo "nr argv insuf"
	exit 1
fi 
if [ ! -d $1 ]
then 
	echo "$1 nu este un director"
	exit 1
fi 
while IFS= read -r  fis; do
	echo "Modificati drepturile pentru $fis la 744:DA/NU"
	read -r raspuns
	if [ $raspuns="DA" ]; then
		chmod 744 "$fis"
		echo "drepturile au fost modificate"
	else
		echo "drepturile nu au fost modificate"
	fi
done< <(find $1 -type f -perm 755 -print)
exit 0

