#!/bin/bash
if [ $# -eq 0 ]
then 
	echo "nr argv invalid"
	exit 1
fi
echo -n "primul cuvant: "
read -r cuv1
echo -n "al doilea cuvant: "
read -r cuv2
for x in $*; do
	if [ ! -f  $x ] ;then
		continue
	fi
	sed -i "s/$cuv1/$cuv2/g" "$x"
	echo "substitutie cu succes"
done
exit 0
