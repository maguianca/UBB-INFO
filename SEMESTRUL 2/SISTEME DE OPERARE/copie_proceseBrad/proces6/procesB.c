#include<stdio.h>                                                       
#include<stdlib.h>                                                      
#include<sys/wait.h>                                                    
#include<sys/stat.h>                                                    
#include<unistd.h>                                                      
#include<fcntl.h>                                       
#include<string.h>
int main(int argc,char** argv)                                          
{           
	if(argc<2){perror("mod utilizare argv[1]:fifo");exit(1);}           
        char* fifo_name=argv[1];                    
        int fd=open(fifo_name, O_RDONLY);
	if(fd==-1){perror("fifo error");exit(1);}
	char voc[]="AEIOU";
	int arr[6];
	for(int i=0;i<5;i++)
        {
                if(read(fd,&arr[i],sizeof(int))<0){perror("error b");close(fd);exit(1);}                
		printf("B voc[%c]: frecventa %d\n",voc[i],arr[i]);
        }
	if(unlink(fifo_name)<0){perror("error unlink");exit(1);}
	return 0;
}
