#!/bin/bash
if [ $# -eq 0 ]
then
	echo "numar insuficient de argumente"
	exit 1
fi 

while true; do 
	proces=$( ps -eo comm=)
	for program in "$@"; do
	if echo "$proces" |grep -qw "$program"; then
		kill $(ps -eo pid,comm=| grep -w "$program" |awk '{print $1}')
		echo "killed dangerous program : $program"
	fi 
done 
sleep 5
done
