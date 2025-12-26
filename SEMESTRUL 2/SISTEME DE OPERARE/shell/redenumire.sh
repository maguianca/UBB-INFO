#!/bin/bash
if [ ! $# -eq 4 ]; then
    echo "nr argv invalid"
    echo "mod utilizare: director, extensie1, extensie2, cuvant"
    exit 1
fi

if [ ! -d "$1" ]; then
    echo "eroare: director invalid"
    exit 1
fi

total=0
while IFS= read -r fis; do
    if file "$fis" | grep -q "ASCII text$"; then
        ext=$(echo "$fis" | awk -F. '$NF>1 {print $NF}')
        if [ -z "$ext" ] || [ "$ext" != "$2" ]; then
            continue
        fi
        nume=$(echo "$fis" | awk -F. '$NF>1 {print substr($0,1,length($0)-length($NF))}')
        apare=$(grep -ci "$4" "$fis")
        total=$((total + apare))
        echo "În $fis apare "$4" de $apare ori"
        echo "$fis se va redenumi în $nume$3"
        mv "$fis" "$nume$3"
    fi
done < <(find "$1" -type f -print)

echo "$4 apare de $total ori"
exit 0

