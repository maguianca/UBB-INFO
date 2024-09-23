#!/bin/sh

# Sa se afiseze, pentru fiecare fisier luat ca si parametru din linia de 
# comanda, numarul de cuvinte care au lungimea mai mare decat un 
# numar k, citit de la tastatura. Afisarea se va face decsrescator 
# dupa numarul de cuvinte.
if [ $# -eq 0 ]
then 
	echo "nr argv insuf"
	exit 1
fi
echo -n "introduceti un nr n: "
read -r "n"
for x in $*; do 
	rezultat=$(cat $x| awk -v n=$n '{for(i=1;i<=NF;i++) if(length($i)>n)print $i;}'|sort|uniq -c|sort -nr -k1,1)
	echo $rezultat
done 
exit 0
