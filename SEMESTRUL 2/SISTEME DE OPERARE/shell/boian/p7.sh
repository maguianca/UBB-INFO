#!/bin/bash
if [ $# -eq 0 ]
then 
	echo "Numar insuficient de argumente"
	exit 1
fi 
if [ ! -f $1 ]
then 
	echo "Error: $1 nu este un nume de fisier valid" 
	exit 1
fi 
email=""

while IFS= read -r username; do
	if finger "$username"| grep -qm 1 Name  ; then
		email+="$username@scs.ubbcluj.ro,"
	fi
done <"$1"
email=$(echo "$email" | sed 's/,$//')
echo "$email"
exit 0
