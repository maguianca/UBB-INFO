#!/bin/bash

if [ $# -eq 0 ]
then 
	echo "nr argv insuf"
	exit 1
fi

while true; do
	for program in $*; do
		pids=`pd -ef| awk -v program=$program 'program==$8 {print$2}'
		for pid in pids; do
			if ! [[ -z $pid ]]; then
				kill -9 $pid
			fi
		done
	done
	sleep(1)
done
exit 0
