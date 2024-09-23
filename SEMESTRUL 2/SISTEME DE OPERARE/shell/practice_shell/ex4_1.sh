#!/bin/bash


if [ $# -ne 1 ]; then
    echo "Mod de utilizare: $0 <numar_minim_IP-uri>"
    exit 1
fi
if ! [[ $1 =~ ^[0-9]+$ ]]; then
        echo "$1 nu este nr natural"
        exit 1
fi

num_minim_IP=$1
declare -A ip_count

while true; do
    while IFS= read -r line; do
        user=$(echo "$line" | awk '{print $1}')
        ip=$(echo "$line" | awk '{print $5}')

        ip_count["$user,$ip"]=1
    done <<< "suport_p4/who.fake"

    for key in "${!ip_count[@]}"; do
        user=$(echo "$key" | cut -d',' -f1)

        num_ip=$(grep -o -E "^$user,[0-9]+(\.[0-9]+){3}" <<< "${!ip_count[@]}" | wc -l)

        if [ "$num_ip" -gt "$num_minim_IP" ]; then
            if ! grep -q "^$user$" users_notified.txt; then
                echo "Contul $user are $num_ip conexiuni."
                echo "$user" >> users_notified.txt
            fi
        fi
    done
    ip_count=()
    sleep 5
done
