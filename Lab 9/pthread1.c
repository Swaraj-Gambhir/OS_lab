#include<pthread.h>
#include<stdio.h>
#include<unistd.h>
int sum[5];
void *threadfn(void *arg)
{
    int id =(int)arg;
    int start;
    start=id*200;
    int count;
    count=0;
    while(count<200)
    {
        sum[id]=sum[id]+start+1;
        count++;
        start++;
        
    }
}

int main()
{
    pthread_t t[5];
    for(int i=0;i<5;i++)
    pthread_create(&t[i],NULL,&threadfn,(void*)i);
    
    for(int i=0;i<5;i++)
    pthread_join(t[i],NULL);
    
    int sumi=0;
    for (int i=0;i<5;i++)
    sumi+=sum[i];
    
    printf("Sum is %d\n",sumi);
    
    
}