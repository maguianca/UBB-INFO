#!/bin/bash 
if [ $# -eq 0 ]
then 
	echo "nr argv insuf"
	exit 1
fi
suma=0
for x in $*; do
	sed -i 's/,/ /g' $x
	sed -i 's/[0-9]+\.[0-9]\+//g' "$x"
	result=$(cat $x|grep -Eo "\b[0-9]+\b")
	for y in $result; do
		echo "$y"
		suma=$(($suma+$y))
	done
done
echo "suma este $suma"
exit 0
