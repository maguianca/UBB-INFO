#!/bin/sh

# Verifică dacă sunt specificate două nume de fișiere ca argumente în linia de comandă
if [ $# -ne 2 ]; then
    echo "Usage: $0 input_file output_file" >&2
    exit 1
fi

# Preia numele fișierelor din argumentele liniei de comandă
input_file=$1
output_file=$2

# Procesează fișierul de intrare și pune în fișierul de ieșire liniile care conțin doar cuvinte formate din litere mici
awk <$input_file '{
    for (i=1; i<=NF; i++)
        if ($i !~ /^[a-z]+$/)
            $i=""
    linie = ""
    for (i=1; i<=NF; i++)
        if ($i != "")
            linie = linie $i " "
    if (linie != "")
        print substr(linie,1,length(linie)-1)
}' | sort -u > $output_file
