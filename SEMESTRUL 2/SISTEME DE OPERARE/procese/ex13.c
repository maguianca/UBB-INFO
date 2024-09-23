/*Procesul A citeste N intregi de la tastatura si ii trimite unui 
proces numit B. Procesul B va adauga un numar aleator, intre 2 si 5, 
la toate numerele primite de la procesul A si le va trimite unui alt 
proces numit C. Procesul C va adauga toate numerele primite si va 
trimite suma inapoi procesului A. Toate procesele vor afisa un mesaj 
cu numerele primite si trimise.*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<signal.h>
//A -> B -> C
int main(int argc, char** argv){
	int a2b[2],b2c[2],c2a[2];
	int r1=pipe(a2b),r2=pipe(b2c),r3=pipe(c2a);
	if(r1==-1||r2==-1||r3==-1){perror("error pipe())");exit(1);}
	int f1=fork();
	if(f1==-1){perror("error fork1())");exit(1);}
	else if(f1==0){
	//suntem in B
		close(c2a[0]);close(c2a[1]);
		close(a2b[1]);close(b2c[0]);
		srandom(time(0));
		int n;
		int* arr;
		if(read(a2b[0],&n,sizeof(int))<0){
			close(a2b[0]);close(b2c[1]);
			perror("error a2b");exit(1);
			
		}
		arr=(int*)malloc(sizeof(int)*n);
		for(int i=0;i<n;i++)
		{
			if(read(a2b[0],&arr[i],sizeof(int))<0){
			         close(a2b[0]);close(b2c[1]);
                                 perror("error a2b");exit(1);}
			printf("B a primit de la A:%d\n",arr[i]);
			arr[i]+=random()%4+2;
		}
		 if(write(b2c[1],&n,sizeof(int))<0){
                        close(a2b[0]);close(b2c[1]);
                        perror("error b2c");exit(1);

                }
                for(int i=0;i<n;i++)
                {
			printf("B trimite la C:%d\n",arr[i]);
                        if(write(b2c[1],&arr[i],sizeof(int))<0){
                                 close(a2b[0]);close(b2c[1]);
                                 perror("error b2c");exit(1);}
                }
		free(arr);
		close(b2c[1]);close(a2b[0]);
		exit(0);
	}
	int f2=fork();
	if(f2==-1){perror("error fork2())");exit(1);}
	else if(f2==0){
	//suntem in C
		close(a2b[0]);close(a2b[1]);
		close(b2c[1]);close(c2a[0]);
		int sum=0,n;
		int* arr;
		if(read(b2c[0],&n,sizeof(int))<0){
			close(b2c[0]);close(c2a[1]);
			perror("error b2c");
			exit(1);
		}
		arr=(int*)malloc(sizeof(int)*n);
		for(int i=0;i<n;i++)
		{
			if(read(b2c[0],&arr[i],sizeof(int))<0){
			 close(b2c[0]);close(c2a[1]);
                        perror("error b2c");
                        exit(1);}
			printf("C a primit de la B %d\n",arr[i]);
			sum+=arr[i];
		}
		free(arr);
		if(write(c2a[1],&sum,sizeof(int))<0){
			close(b2c[0]);close(c2a[1]);
                        perror("error c2a");
                        exit(1);}
		printf("C trimite la A %d\n",sum);
		close(b2c[0]);close(c2a[1]);
		exit(0);
	}
	//A-parinte
	close(a2b[0]);
	close(b2c[0]);close(b2c[1]);
	close(c2a[1]);
	int n, *arr;
	printf("n= ");
	scanf("%d",&n);
	if(write(a2b[1],&n,sizeof(int))<0)
	{
			perror("error a2b");exit(1);
			close(a2b[1]);close(c2a[0]);
	}
	arr=(int*)malloc(sizeof(int)*n);
	for(int i=0;i<n;i++){
		printf("arr[%d]= ",i);
		scanf("%d",&arr[i]);
	}
	for(int i=0;i<n;i++)
	{
		printf("A trimite la B: %d\n",arr[i]);
		if(write(a2b[1],&arr[i],sizeof(int))<0)
		 {
                        perror("error a2b");exit(1);
                        close(a2b[1]);close(c2a[0]);
        	}
	}
	free(arr);
	int sum;
	if(read(c2a[0],&sum,sizeof(int))<0)
	 {
                        perror("error c2a");exit(1);
                        close(a2b[1]);close(c2a[0]);
          }
	printf("A a primit de la C:%d\n",sum);
	close(a2b[1]);close(c2a[0]);
	wait(0);
	wait(0);
	return 0;
}
