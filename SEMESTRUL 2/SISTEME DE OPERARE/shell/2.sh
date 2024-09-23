#!/bin/bash

nr=$(find $1 -type f |awk -F'/' '{print $NF}'|sort|uniq -u)
while IFS= read -r line;do
        echo $line
done<<<"$nr"

