#!/bin/bash

        sum=0
        count=0
        find . -type d |while IFS= read -r file;do
                linii=$(wc -l < "$file")
                NR=$(grep -c -E "^[ ]*$" "$file")
                count=$((count + 1))
                temp=$((linii - NR))
                sum=$((sum + temp))
                echo "$file $linii $NR $count $sum"
        done
                echo $(($sum/ $count))


