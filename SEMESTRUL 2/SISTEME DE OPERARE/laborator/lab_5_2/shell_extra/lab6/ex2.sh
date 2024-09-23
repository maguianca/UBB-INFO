#!/bin/bash 
if [ $# -eq 0 ]
then 
	echo "nr argumente insuficient"
	exit 1
fi 
if [ ! -f $1 ]
then 
	echo "$1 nu este nume de fisier valid"
	exit 1
fi 
MAX_LEN=0
NL=1
LINIA=0
while IFS= read -r LINIE
do
	LEN=${#LINIE}
	if [ $LEN -gt $MAX_LEN ]
	then
		MAX_LEN=$LEN
		LINIA=$NL	
	fi
	NL=$(($NL+1))
done<$1
sed -n ''$LINIA'p' $1
echo "Linia $LINIA contine $MAX_LEN caractere"
exit 0
