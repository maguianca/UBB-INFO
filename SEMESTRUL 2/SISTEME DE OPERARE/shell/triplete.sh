#!/bin/bash
if [ $# -lt 3 ]; then
    echo "nr argv invalid"
    echo "mod utilizare: fisier, cuvant ,numar"
    exit 1
fi
while true; do
    if [ -z "$1" ] || [ -z "$2" ] || [ -z "$3" ]; then
	shift 3 
	break
    fi
    if [ ! -f "$1" ]; then
	echo "$1 nu e nume de fisier valid" 
	shift 3 
	continue
    fi
    if ! [[ "$3" =~ ^[0-9]+$ ]]; then 
	echo "$3 nu e numar valid"
	shift 3 
	continue 
    fi
    if file "$1" | grep -q "ASCII text$"; then
        awk -v cuv="$2" -v fisier="$1" -v numar="$3" '\
            { k=0; for(i=1; i<=NF; i++) if($i==cuv) k++; \
            if(k==numar) print fisier, $0; }' "$1"
    fi
    shift 3
done
exit 0

