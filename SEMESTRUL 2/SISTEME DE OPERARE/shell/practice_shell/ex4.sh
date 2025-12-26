y#!/bin/bash
if [ $# -eq 0 ];then 
	echo "nr argv insuf"
	echo "utilizare $1 nr natural"
	exit 1
fi
if ! [[ $1 =~ ^[0-9]+$ ]]; then 	
	echo "$1 nu este nr natural"
	exit 1
fi
rez=$(cat "suport_p4/who.fake"| awk '{print $1}' |sort  |uniq -c|sort -nr -k1,1)
cnt=1
while true; do
	rez=$(echo $rez| tail -n +$cnt)
	echo $rez
	user=$(echo $rez| head -n 1 | awk '{print $2}')
	ip=$(echo $rez| head -n 1 | awk '{print $1}')
	if [[ $ip -gt $1 ]]; then 
		echo "Contul $user are $ip conexiuni"
	fi
	cnt=$(($cnt+1))
	sleep 5
done
exit 0
