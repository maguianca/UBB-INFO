#!/bin/bash
find . -type f -name "*.txt"|while IFS= read -r line;do
	nr=$(grep -E -c "cat" "$line")
	if [[ $nr -gt 0 ]];then
		echo $(basename $line)
	fi
done
