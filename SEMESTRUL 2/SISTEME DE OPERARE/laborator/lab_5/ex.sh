
BEGIN{
	count=0
}

{
	for (i=1; i<$NF; i++)
	{
		$i=="mere"
		count++
	}
}

END{
	print "Numarul aparitii: " count
}
