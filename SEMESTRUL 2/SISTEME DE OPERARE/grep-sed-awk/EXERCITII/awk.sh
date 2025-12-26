#!/bin/awk
BEGIN{
suma=0
maxim=0
}
{
suma=$1+10*$3
if (suma>maxim)
	maxim=suma

}
END{
print "Maximul este",maxim
}

