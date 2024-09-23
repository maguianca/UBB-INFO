#!/bin/bash
if [ $# -eq 0 ]
then 
	echo "nr argv insuficiente"
	exit 1
fi 
if [ ! -d $1 ]
then 
	echo "$1 nu este un director"
	exit 1
fi 
while IFS= read -r fis; do
	if file $fis| grep -q "ASCII text$" ;then
		if cat $fis| grep -qE "[0-9]{5,}";then
			echo `grep -E "[0-9]{5,}" $fis`
			echo $fis
		fi
	fi
done< <(find $1 -type f -print)
exit 0
