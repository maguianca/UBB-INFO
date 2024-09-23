#!/bin/bash

if [ $# -eq 0 ]; then
    echo "Număr insuficient de argumente"
    exit 1
fi

if [ ! -d "$1" ]; then
    echo "Eroare: $1 nu este un director valid"
    exit 1
fi

linii_t=0
fisiere_t=0

while IFS= read -r Fisier; do
    if file "$Fisier" | grep -q 'ASCII text$'; then
        linii=$(wc -l < "$Fisier")
        linii_t=$((linii_t + linii))
        fisiere_t=$((fisiere_t + 1))
    fi
done < <(find "$1" -type f -print)

if [ "$fisiere_t" -gt 0 ]; then
    medie=$(($linii_t / $fisiere_t))
else
    medie=0
fi

echo "Linii: $linii_t  Fisiere: $fisiere_t  Medie: $medie"
exit 0

