#!/bin/bash
if [ ! $# -eq 2 ]
then 
	echo "nr arg invalid"
	exit 1
fi 
if [ ! -d "$1" ]
then 
	echo "$1 nu este nume de fisier valid"
	exit 1
fi 
if  ! [[ "$2" =~ ^[0-9]+$ ]]
then 
	echo "$2 nu este un numar valid"
	exit 1
fi 
D=$1
N=$2

for fis in `find $D -type f -perm -u=rx`; do
	echo $fis
	head -$N $fis
done 
exit 0
