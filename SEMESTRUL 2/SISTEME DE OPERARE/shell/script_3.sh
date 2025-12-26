#!/bin/bash
# check-process-count.sh maxim
# maxim este numarul maxim de procese admis
maxim=$1
for user in `who | awk '{ print$1 }'` ; do
    if [ `ps -u $user | wc -l` -ge $maxim ] ; then
    echo $user
    write $user <<MESAJ
Aveti prea multe procese
MESAJ
    fi
done
