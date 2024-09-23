#include "common.h"
void make_fifo(char* fifo_name)
{
	if(mkfifo(fifo_name,0600)<0)
	{
		perror("error on fifo");
		exit(1);
	}
}
int main(int argc, char* argv[])
{
	if(argc!=3)
	{
		perror("nr insuf de argm");
		perror("mod utilizare: argc[1]:fifo argv[2]: filename");
		exit(1);
	}
	char* fifo_name=argv[1];
	char* file_name=argv[2];
	make_fifo(fifo_name);
	int fd=open(fifo_name,O_WRONLY);
	if(fd<0){perror("error fifo writing");exit(1);}
	FILE* file=fopen(file_name,"r");
	if(file==NULL){
		perror("error opening file");
		close(fd);
		exit(1);
		}
	char c;
	while(fscanf(file, "%c",&c)>0)
	{
		if(c>='0' && c<='9')
		{
			printf("am citit: %c\n",c);
			if(write(fd,&c,1)<0)
			{
				perror("error fifo");
				fclose(file);
				close(fd);
				exit(1);
			}

		}
	}
	fclose(file);
	close(fd);
	return 0;
}
