#!/bin/bash
if [ $# -eq 0 ]
then 
	echo "nr argv insuf"
	exit 1
fi
if [ ! -f $1 ]
then 
	echo "$1 nu e nume de fisier"
	exit 1
fi 
while IFS= read -r linie; do
	if finger "$linie"| grep -q Name; then 
		email+="$linie@scs.ubbcluj.ro,"		

	fi
done <"$1"
email=$(echo "$email" | sed 's/,$//')
echo $email
exit 0
