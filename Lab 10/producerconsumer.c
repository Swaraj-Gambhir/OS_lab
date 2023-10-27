#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include<sys/wait.h>
#define BUFFER_SIZE 5
#define MAX_ITEMS 10

int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;
int produce = 0;
int consumed = 0;

sem_t mutex;
sem_t full;
sem_t empty;

void *producer(void * arg)
{
	int item=1;
	while(produce<MAX_ITEMS)
	{
		sem_wait(&empty);
		sem_wait(&mutex);
		buffer[in]=item;
		printf("Producing item %d\n",item);
		in=(in+1)%BUFFER_SIZE;
		item++;
		produce++;
		
		sem_post(&mutex);
		sem_post(&full);
		if(item>6)
		sleep(1);
	}
	pthread_exit(NULL);
}

void *consumer(void * arg)

{
	while(consumed<MAX_ITEMS)
	{
		sem_wait(&full);
		sem_wait(&mutex);
		int item=buffer[out];
		printf("Consuming item %d\n",item);
		out=(out+1)%BUFFER_SIZE;
		consumed++;
		sem_post(&mutex);
		sem_post(&empty);
	}
	pthread_exit(NULL);
}
int main() 
{
   pthread_t producerT, consumerT;

   sem_init(&mutex, 0, 1);
   sem_init(&full, 0, 0);
   sem_init(&empty, 0, BUFFER_SIZE);

   pthread_create(&producerT, NULL, producer, NULL);
   pthread_create(&consumerT, NULL, consumer, NULL);

   pthread_join(producerT, NULL);
   pthread_join(consumerT, NULL);

   sem_destroy(&mutex);
   sem_destroy(&full);
   sem_destroy(&empty);

   return 0;
}