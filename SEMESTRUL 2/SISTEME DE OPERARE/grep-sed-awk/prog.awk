BEGIN {
prod=1
}
NR<=2{
{printf$2}
{printf$3}
diff=$2-$3 	
 prod *= diff
}
END {
 print prod
}

