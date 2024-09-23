#!/bin/bash
if [ $# -eq 0 ]
then 
	echo "nr argumente insuficient"
	exit 1
fi
if [ ! -d $1 ]
then 
	echo "$1 nu e un director"
	exit 1
fi

while IFS= read -r fis
do 
	if file $fis | grep -q "ASCII text$" ; then 
		NL=$(wc -l < "$fis")
		if [ $NL -lt 6 ]; then
			cat "$fis"
		else 
			head -n 3 "$fis"
			tail -n 3 "$fis"
		fi
	fi
done < <(find $1 -type f -print)
exit 0
