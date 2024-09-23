#!/bin/bash
#se citeste fisiere date de utilizator pana cand unul dintre acestea contine
#toate cuvinteleb din linia de comanda
if [ $# -eq 0 ]
then 
	echo "nr argv insuficiente"
	echo "mod utilizare: $1,$2..... cuvinte"
	exit 1
fi
cuvinte=()

cnt=0
for x in $*; do
	cnt=$(($cnt+1))
	cuvinte[$cnt]="$x"
done
while true; do
	frecventa=()
	echo -n "Introduceti un fisier valid:  "
	read -r fisier
	if [ ! -f $fisier ]; then 
		echo "$fisier nu e nume de fisier valid"
		continue
	fi
	for (( j=1;j<=$cnt;j++));do
		if ! [[ `grep -E -c "${cuvinte[$j]}" $fisier` -eq 0 ]]; then
			frecventa[$j]=1;
		else 
			continue
		fi 
	done
	ok=1
	for((j=1;j<=$cnt;j++));do
		if [[ "${frecventa[$j]}" -ne 1 ]]; then
			ok=0
		fi
	done
	if [ $ok -eq 1 ]; then 
		echo "in $fisier apar toate cuvintele"
		break
	fi
done
exit 0
