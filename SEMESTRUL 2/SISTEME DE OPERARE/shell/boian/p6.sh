#!/bin/bash
if [ $# -eq 0 ]
then 
	echo "Numar insuficient de argumente"
	exit 1
fi
if [ ! -d $1 ]
then
	echo "Error: $1 nu este director"
	exit 1
fi
files_with_write_permissions=$(find "$1" -type f -perm -o+w)

while IFS= read -r file; do
	echo "Fisier: $file"
	echo "Permisiunile inainte de modificare: $(ls -l $file| cut -d ' ' -f 1)"
	chmod o-w "$file"
	echo "Permisiunile dupa modificare:$(ls -l $file | cut -d ' ' -f 1)"
	
done <<<"$files_with_write_permissions" 

