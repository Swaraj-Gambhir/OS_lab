#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include<sys/wait.h>
#define BUFFER_SIZE 10

int buffer[BUFFER_SIZE];
int  r= 0;
int w = 0;
int readcount=0;

sem_t mutex;
sem_t write;
sem_t readd;

void *reader(void * arg)
{
	
	sem_wait(&mutex);
	readcount++;
	if(readcount>0)
	{sem_wait(&write);}
	sem_post(&mutex);
	
	int ri=0;
	while(ri<w)
	{
		printf("%d",buffer[ri++]);
	}
	
	
	sem_wait(&mutex);
	readcount--;
	if(readcount==0)
	sem_post(&write);
	sem_post(&mutex);
	
	pthread_exit(NULL);
}

void *writer(void * arg)

{
	
	while(w<BUFFER_SIZE)
	{
	sem_wait(&write);
	printf("Enter next letter\n");
	int c;
	scanf("%d",&c);
	if(c==0)
	{
		sem_post(&write);
		sleep(5);
		sem_wait(&write);
		
	}
	else
	{
	buffer[w++]=c;
	}
	sem_post(&write);
	}
	
	pthread_exit(NULL);
}
int main() 
{
   pthread_t writerT,readerT1,readerT2,readerT3,readerT4,readerT5;

   sem_init(&mutex, 0, 1);
   sem_init(&write, 0, 1);
sem_init(&readd, 0, 1);	
   pthread_create(&writerT, NULL, writer, NULL);
   pthread_create(&readerT1, NULL, reader, NULL);
   pthread_create(&readerT2, NULL, reader, NULL);
   pthread_create(&readerT3, NULL, reader, NULL);
   pthread_create(&readerT4, NULL, reader, NULL);
   pthread_create(&readerT5, NULL, reader, NULL);
   
   pthread_join(writerT, NULL);
   pthread_join(readerT1, NULL);
  pthread_join(readerT2, NULL);
   pthread_join(readerT3, NULL);
   pthread_join(readerT4, NULL);
   pthread_join(readerT5, NULL);

   sem_destroy(&mutex);
   sem_destroy(&write);
   sem_destroy(&readd);

   return 0;
}