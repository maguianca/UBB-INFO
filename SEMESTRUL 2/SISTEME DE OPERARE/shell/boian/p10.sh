#!/bin/bash

last -s $(date -d "2024-03-01 00:00:00" +%s) -t $(date -d "2024-03-30 23:59:59" +%s) 
| grep -v 'wtmp'| awk '{print $1}' | sort| uniq -c| sort -nr
