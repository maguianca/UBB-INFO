#!/bin/bash
if [ $# -eq 0 ]
then 
	echo "Nr argumente insuficient"
	exit 1
fi
if ! [[ $1 =~ ^[0-9]$ ]]
then
	echo "Nr furnizat $1 nu e un numar valid"
	exit 1
fi 
for x in $(seq 1 $1 )
do 
	touch "file_$x.txt"
	sed -n "$x,+4p" /etc/passwd >"file_$x.txt"
done
exit 0
