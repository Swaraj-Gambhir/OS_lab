#include<pthread.h>
#include<stdio.h>
#include <semaphore.h> 
#include <unistd.h> 
  
sem_t mutex,mutex1; 
void display(char v)
{
printf("I am in thread via %c\n",v);
}
void *func_a()
{
   char v='a'; 
   sem_wait(&mutex); 
    display(v);
    
    sem_post(&mutex1); 
    
    
    sleep(2);
    sem_wait(&mutex);
  display(v);
  sem_post(&mutex1); 
  

}

void *func_b()
{
  char v='b';
  
  
  sem_wait(&mutex1); 
    display(v);
  sem_post(&mutex); 
    sleep(2);
   sem_wait(&mutex1); 
    display(v);
    sem_post(&mutex); 
}


int main()
{
	
    pthread_t a,b;//0 for add,1 for sub,2 for multiplication
    //int answer[3][3][3];
    sem_init(&mutex, 0, 1); 
    sem_init(&mutex1, 0, 0);
    	pthread_create(&a,NULL,&func_a,NULL);
    	pthread_create(&b,NULL,&func_b,NULL);
    	
    	
   
    
  
    pthread_join(a,NULL);
    pthread_join(b,NULL);
    
    
	sem_destroy(&mutex); 
return 0;
}