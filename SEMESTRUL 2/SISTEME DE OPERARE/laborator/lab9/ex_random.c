#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<time.h>
int main(int argc, char** argv)
{
	//initializez generatorul -val initiala
	srandom(time(NULL));
	int i=0;
	while(i<10)
	{
		printf("%d: %d\n",i,1+rand()%100);
		i++;
	}
	return 0;
}
