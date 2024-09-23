y#!/bin/bash 
if [ $# -eq 0 ]
then 
	echo "numar insuf de argv"
	exit 1
fi
if [ ! -f $1 ]
then 
	echo "nu e $1 nume de fis valid"
	exit 1
fi
while IFS= read -r linie; do
	NL=${#linie}
	cuvinte=$(echo "$linie"| grep -E "[a-z]*[0-9]*")
	for((i=0;i<NL-1;i++));do
		for((j=i+1;j<=NL;j++));do
			cuvant1=$(echo "$cuvinte"| awk -v i=$i '{print $i}')
			cuvant2=$(echo "$cuvinte"|awk -v j=$j '{print $j}')			
			if [ "$cuvant1" = "$cuvant2" ]; then
				echo "$linie"
				break 2
			fi
		done
	done
done < "$1"
exit 0
