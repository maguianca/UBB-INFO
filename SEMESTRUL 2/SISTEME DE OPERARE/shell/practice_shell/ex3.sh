#!/bin/bash

if [ $# -lt 3 ]
then 
	echo "nr insuf de argv"
	echo "mod untilizare: 1 nume fct C, 2 nume librarie, 3..fis/dir"
	exit 1
fi
functie=$1
librarie=$2
shift 2
for x in $*; do
	if [ -f $x ]; then
		if [[ $x =~ .c$ ]]; then
			if [ $(grep -E -c -o "$functie" "$x") -gt 0 ];then
				 echo " in $x am gasit $functie functia"
				if [ $(grep -E -o -c "$librarie" "$x") -eq 0 ]; then
					echo "am inclus"
					sed '1i "#include<$librarie>"' $x
				else
					echo "este deja inclusa biblioteca"
				fi
			fi
		else
			continue
		fi

	elif [ -d $x ]; then
		while IFS= read -r file;do
                        if [ $(grep -E -c -o "$functie" "$file") -gt 0 ]; then
				echo " in $file am gasit $functie functia"
                                if [ $(grep -E -o -c "$librarie" "$file") -eq 0 ]; then                                       
 					sed -i '1i #include<'$librarie'>' $file
					echo "am inclus"
                                else
					echo "este deja inclusa biblioteca"
				fi
                        fi
		done< <(find $x -type f -name "*.c")
	else
		echo "$x nu este nici director nici fisier"
		continue
	fi
done
exit 0
