#!/bin/bash
if [ $# -eq 0 ]
then 
	echo "nr insuf de argumente"
	exit 1
fi 
if [ ! -d $1 ]
then 
	echo "$1 nu este nume de director valid"
	exit 1
fi
total_f=0
total_l=0
while IFS= read -r f ; do
	if file $f | grep -q "ASCII text$"; then
		linii=$(cat $f| wc -l)
		total_f=$(($total_f + 1))
		total_l=$(($total_l + $linii))
	fi
done< <(find $1 -type f -print)
if [ $total_f -gt 0 ]
then 
	medie=$(( $total_l/$total_f ))
else
	medie=0
fi 
echo "Fisiere $total_f Linii $total_l Medie $medie"
exit 0
