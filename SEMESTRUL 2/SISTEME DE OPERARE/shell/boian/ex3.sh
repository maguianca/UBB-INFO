#!/bin/bash

if [ $# -eq 0 ]
then 
	echo "nr argv insuficient"
	exit 1
fi 
if [ ! -d $1 ]
then 
	echo "$1 nu e nume de director valid"
	exit 1
fi 
while IFS= read -r fis; do
	sort "$fis" > "${fis}.sort"
	mv "${fis}.sort" "$fis"	

done< <(find $1 -type f -name "*.log")
echo "toate fisierele .log au fost sortate"
exit 0
