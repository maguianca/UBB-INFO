#!/bin/bash
suma=0
linii=0
find . -type f -name "*.cc"|while IFS= read -r line;do
	nr=$(grep -E -v -c "^[ \t]*[^ ][ \t]*$" "$line");
	linii=$((linii+1))
	suma=$((suma+nr))
done
echo "$suma"
echo "$linii"
#echo $((suma/linii))
