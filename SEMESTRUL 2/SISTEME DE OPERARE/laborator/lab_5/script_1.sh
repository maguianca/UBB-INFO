#!/bin/bash

#./ex1.sh N file1 file2........
#verific numarul de argumente
if [ $# -eq 0 ]  
then
	echo" NUMAR INSUFICIENT DE ARGUMENTE!"
	echo" Utilizare: $0 N"
	exit 1 
fi



N=$1
#shift
#for FILE in $*

for X in $(seq 1 $N)
do 
	#cream fisier
	touch "file_$X.txt"
	#scriem in fisier
	sed -n "$X,+4p" /etc/passwd > "file_$X.txt"	
done
exit 0
