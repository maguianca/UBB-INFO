#include<unistd.h>
#define MAX_THR 10
#define MAX_SIZE 100
pthread_mutex_t mtx=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond=PTHREAD_COND_INITIALIZER;
int buffer[100];
int fd,sum=0;
int flag=0;//0 buffer gol// 1 buffer plin
void*consume(void*arg){
         int id=*(int*)arg;
        free(arg);
        pthread_mutex_lock(&mtx);
        while(flag==0){
                printf("[thread %d] wait..\n",id);
                pthread_cond_wait(&cond,&mtx);
        }
        for(int i=0;i<MAX_SIZE;i++){
                sum+=buffer[i];
        }
         printf("[thread %d] sum= %d\n",id,sum);
        flag=0;
        pthread_cond_signal(&cond);//semnaleaza la producers
        pthread_mutex_unlock(&mtx);
        return NULL;

}
void*produce(void*arg){
        int id=*(int*)arg;
        free(arg);
        pthread_mutex_lock(&mtx);
        while(flag==1){
                pthread_cond_wait(&cond,&mtx);
        }
        for(int i=0;i<MAX_SIZE;i++){
                 printf("[thread %d] produce..\n",id);
                //read(fd,&buffer[i],sizeof(int));
                        //if (read(fd, &buffer[i], sizeof(int)) != sizeof>                perror("read()");
                buffer[i]=rand()%1200;
		exit(1);
            }
                 //printf("[thread %d] produce..\n",id);
                //buffer[i]=rand()%2000;
        }
        flag=1;
        pthread_cond_signal(&cond);//semnaleaza la consumers
        pthread_mutex_unlock(&mtx);
        return NULL;

}
int main(int argc,char**argv)
{
        //generare 100000 de numere aleatoare
        srand(time(NULL));
        //int fd=open("file.bin",O_RDONLY);
        //if(fd==-1){perror("open()");exit(1);}
        for(int i=0;i<MAX_SIZE;i++)
                buffer[i]=rand()%1200;
        pthread_t tc[MAX_THR],tp[MAX_THR];
        //close(fd);
        for(int i=0;i<MAX_THR;i++)
        {
                int *idc=malloc(sizeof(int));
                *idc=i;
                int *idp=malloc(sizeof(int));
                *idp=i;
                pthread_create(&tc[i],NULL,consume,idc);
                pthread_create(&tp[i],NULL,produce,idp);
        }
         for(int i=0;i<MAX_THR;i++)
        {
                pthread_join(tc[i],NULL);
                pthread_join(tp[i],NULL);
        }
        printf("SUMA: %d\n",sum);
        //close(fd);
        return 0;
}
