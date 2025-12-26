#!/bin/bash

if [ $# -eq 0 ]
then 
	echo "nr argv insuficiente"
	exit 1
fi 
while true; do
	if [ -z $1 ] || [ -z $2 ] || [ -z $3 ]; then
		break
	fi
	if [ ! -f $1 ];then
		echo "nu e nume de fisier" 
		shift 3
		continue
	fi
	if ! [[ $3 =~ ^[0-9]$ ]]; then
		echo "nu e nr valid"
		shift 3
		continue
	fi
	awk -v fis=$1 -v cuv=$2 -v n=$3 '\
	{k=0; for(i=1;i<=NF;i++) if($i==cuv)k++;\
	if (k==n) print $0;}' "$1"
shift 3
done
