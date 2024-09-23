#!/bin/bash
if [ $# -eq 0 ]
then 
	echo "nr argv invalid"
	exit 1
fi
echo -n "introduceti cuvantul : "
read -r cuvant
for x in $*; do
	if [ ! -f "$x" ];then 
		continue
	fi
	awk -v cuv=$cuvant '\
	{k=0; for(i=1;i<=NF;i++) if($i==cuv) k++; }\
        END{ print "Apare de ",k,"ori"}' <"$x"
done
exit 0
