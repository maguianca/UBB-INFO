#!/bin/bash
if [ $# -eq 0 ]
then 
	echo "nr argv insuficiente"
	exit 1
fi
if [ ! -d $1 ]
then 
	echo "$1 nu e nume de director"
	exit 1
fi
while IFS= read -r fis; do
	if [ ${#fis} -le 8 ]; then
		echo "Fisier: $fis"
		if file $fis |grep -q "ASCII text$"; then
			head "$fis"
		fi
	fi
done< <(find $1 -type f -print)
