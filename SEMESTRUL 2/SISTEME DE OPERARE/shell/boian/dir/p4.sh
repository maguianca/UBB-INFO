#!/bin/bash
if [ $# -ne 1 ]; then
	echo "numar argumente insuficient"
	exit 1
fi 
if [ ! -d "$1" ];then 
	echo "Error: $1 nu e un director"
	exit 1
fi
find "$1" -type l | while IFS= read -r link; do
	if[ ! -e "$link" ]; then
		echo "Symbolic link "$link" points to a file/directory that no longer exists"
	fi
done
exit 0
