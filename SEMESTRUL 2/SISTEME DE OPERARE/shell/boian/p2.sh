#!/bin/bash
if [ $# -eq 0 ]
then
        echo" NUMAR INSUFICIENT DE ARGUMENTE!"
        echo" Utilizare: $0 N"
        exit 1
elif [ ! -d $1 ]
then
        echo "Numele furnizat nu este un director "
        exit 2
fi

FILES=$(find $1 -type f)
cnt=0
for FILE in $FILES
do
        if file $FILE| grep -q 'ASCII text$' && [[ "$FILE"==*.c$ ]] 
        then
                NL=$(cat $FILE | wc -l)
                if [ $NL -ge 500 ] 
                then
			if [ $cnt -lt 2 ]; then
                        	echo Fisier: $FILE
				cnt=$((cnt+1))
                	else
				break
			fi
		
                fi
        fi
done

exit 0
