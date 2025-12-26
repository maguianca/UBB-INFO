#!/bin/bash 

FILES =$(ls -l)
for FILE in $FILES 
do 
	echo $FILE
done 
