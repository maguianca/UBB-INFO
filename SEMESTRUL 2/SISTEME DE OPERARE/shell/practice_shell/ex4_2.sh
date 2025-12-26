#!/bin/bash
if [ $# -eq 0 ]
then 
	echo "nr argv insuf"
	echo "mod utilizare: $1 nr natural"
	exit 1
fi
if ! [[ $1 =~ ^[0-9]+$ ]]; then
	echo "nu este $1 nr valid"
	exit 1
fi
numar=$1
touch "fisier.all"
while true; do
	conexiuni=()
	nume=()
	cnt=0
	for user in $(cat "suport_p4/who.fake"|awk '{print $1}'|sort|uniq -c| awk '{print $2}');do
		ips=$(grep -E "$user" "suport_p4/who.fake" |awk '{print $5}'| sort| uniq| tr ' ' '\n'| wc -l )
                cnt=$(($cnt+1))
		conexiuni[$cnt]=$ips
		nume[$cnt]="$user"
	done
	max=0
	username=0
	ok=0
	for ((i=1;i<=$cnt;i++));do
		if [[ "${conexiuni[$i]}" -ge $1 ]] && [[ $(grep -E -c "${nume[$i]}" "fisier.all") -eq 0 ]]
		then
			ok=1 	
			max="${conexiuni[$i]}"
			username="${nume[$i]}"
		fi
	done
	if [ $ok -eq 1 ]; then 
		echo "$username $max"
  		echo "$username" >> "fisier.all"
	else 
		break
	fi
	sleep 5
done
rm "fisier.all"
exit 0
