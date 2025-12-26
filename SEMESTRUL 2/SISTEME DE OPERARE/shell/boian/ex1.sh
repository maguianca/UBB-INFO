#!/bin/bash

for x in `cut -d' ' -f1 who.fake`; do
	numar=0
	for y in `tail -n +1 ps.fake | cut -d' ' -f1 ps.fake`; do
		if [ $x = $y ]; then 
			numar=$(($numar+1))
		fi
	done
	echo "$x $numar"
done 
exit 0
