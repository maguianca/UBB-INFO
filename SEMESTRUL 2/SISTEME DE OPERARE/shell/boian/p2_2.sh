#!/bin/bash
if [ $# -eq 0 ]; then
    echo "NUMAR INSUFICIENT DE ARGUMENTE!"
    echo "Utilizare: $0 N"
    exit 1
elif [ ! -d "$1" ]; then
    echo "Numele furnizat nu este un director"
    exit 2
fi

cnt=0
while IFS= read -r -d '' FILE; do
    if [ -f "$FILE" ] && file "$FILE" | grep -q 'ASCII text' && [[ "$FILE" == *.c ]]; then
        NL=$(wc -l < "$FILE")
        if [ $NL -gt 500 ]; then
            if [ $cnt -lt 2 ]; then
                echo "Fisier: $FILE"
                cnt=$((cnt+1))
            else
                break
            fi
        fi
    fi
done < <(find "$1" -type f -name "*.c" -print0)

exit 0
