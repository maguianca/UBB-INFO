#!/bin/bash
if [ $# -eq 0 ]
then
	echo "nr argv insuf"
	echo "mod utilizare: $1 nume_fisier"
	exit 1
fi 
nume=$1
touch ${nume}.txt
for ((i=1;i<=5;i++)); do
	echo "$i" >> "${nume}.txt"
done
echo -n "introduceti un nume fisier: "
read -r fisier
touch $fisier
while true; do
	read -r citire
	if [[ $citire == "stop" ]]
	then 
		break
	fi
	echo $citire >> $fisier
done
exit 0
