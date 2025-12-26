#!/bin/bash

# Sa se creeze un fisier care contine numele tuturor fisierelor text 
# dintr-un director dat ca parametru si din subdirectoarele acestuia 
# care au cuvinte mai lungi de n caractere (n se citeste de la 
# tastatura). Fisierul va fi ordonat alfabetic.
if [ $# -eq 0 ]
then 
	echo "nr argv incorect"
	exit 1
fi
if [ ! -d $1 ]
then 
	echo "$1 nu e director"
	exit 1
fi
echo -n "introduceti un n: "
read -r n
touch "$1.sort"
while IFS= read -r fis; do
	rez=$(cat $fis| awk -v n=$n '{for(i=1;i<=NF;i++) if(length($i)>n) print $i}'|wc -l)
	echo $rez
	if [ $rez -gt 0 ];then
		echo "$fis" >> "$1.sort"
	fi
done< <(find $1 -type f -name "*.txt")
sort "$1.sort"
cat "$1.sort"
rm "$1.sort"
exit 0
