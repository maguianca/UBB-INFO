#!/bin/bash

read -p "Fisier: " FILE
read -p "Numar linii: " NL

#sed -n ''$NL'p' $FILE
awk 'NR == '$NL'' $FILE 
#in action{} nu merge
