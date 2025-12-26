#!/bin/bash
if [ $# -eq 0 ]
then
        echo "numar insuf de argv"
        exit 1
fi
if [ ! -f $1 ]
then
        echo "nu e $1 nume de fis valid"
        exit 1
fi
while IFS= read -r linie; do
        for cuvant in $linie; do
                nr=$(echo "$linie"| grep -E -o "\<$cuvant\>"|wc -l)
		if [ $nr -ge 2 ]; then
			echo "$linie"
			break
		fi
	done
done < "$1"
exit 0

