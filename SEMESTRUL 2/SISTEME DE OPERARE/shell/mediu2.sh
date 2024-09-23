#!/bin/bash
if [ $# -eq 0 ]
then
        echo "numar insuficient de argumente"
        exit 1
fi
if [ ! -d "$1" ]
then
        echo "Error: $1 nu este nume de director valid"
        exit 1
fi
linii_t=0
fisiere_t=0
find "$1" -type f -print| sort | while IFS= read -r Fisier; do
        if file "$Fisier" | grep -q 'ASCII text$'
        then
                linii=$(wc -l < "$Fisier")
                linii_t=`expr $linii_t + $linii`
                fisiere_t=$(($fisiere_t + 1))
		echo $linii_t >/tmp/${LOGNAME}linii_t
		echo $fisiere_t >/tmp/${LOGNAME}fisiere_t
        fi
done
fisiere_t=`cat /tmp/${LOGNAME}fisiere_t`
linii_t=`cat /tmp/${LOGNAME}linii_t`
rm /tmp/${LOGNAME}fisiere_t /tmp/${LOGNAME}linii_t
if [ "$fisiere_t" -gt 0 ]; then
        medie=$(($linii_t / $fisiere_t))
else
        medie=0
fi
echo "Linii $linii_t Fisiere $fisiere_t Medie $medie"
exit 0

