#!/bin/bash
if [ $# -eq 0 ]
then
	echo "numar invalid argumente"
	exit 1
fi
if [ ! -d $1 ]
then 
	echo "eroare: $1 nu este un director" 
	exit 1
fi 
echo -n "introduceti n:"
read  n 

if ! [[ "$n" =~ ^[0-9]+$ ]]
then 
	echo "$n nu este un numar valid"
	exit 1
fi

for fis in `find "$1" -type f -print`; do
	if  file $fis | grep -q "ASCII text$" 
	then 
		awk -v n="$n" -v fis="$fis" '
            { for (i=1; i<=NF; i++) if (length($i) > n) print fis }
        ' < "$fis"
	fi
done| sort -ru > "rezultat"
cat "rezultat"
exit 0
