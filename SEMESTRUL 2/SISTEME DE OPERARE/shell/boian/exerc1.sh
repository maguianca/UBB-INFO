#!/bin/bash

for user in $(cat "who.fake"|awk '{print $1}'); do
	rez=$(cat "ps.fake"| awk -v user=$user '{if($1==user) print $1}'|sort|uniq -c| awk '{print $1}')
	echo "$user $rez"
done
exit 1
