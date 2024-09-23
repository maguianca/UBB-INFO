#!/bin/awk
BEGIN{
	sum=0
}

{
	sum+=$2
}

END{
rez=sum/NR
print "Suma este ",rez
}
