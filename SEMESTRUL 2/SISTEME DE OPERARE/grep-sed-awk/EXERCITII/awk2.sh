#!/bin/awk 
BEGIN{
	minute=0
	x_minute
}
{	
	minute=0
	if (NF==3){
		minute=$2*60+$3
	}
	if (minute>=x_minute){
		print $1,minute
	}
}
END{
	print "SFARSIT DIN ",NR,"PERSOANE"
}


