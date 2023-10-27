#include<pthread.h>
#include<stdio.h>
#include<unistd.h>
int sum[5];
int m1[3][3];
int m2[3][3];
int add[3][3];
int sub[3][3];
int mul[3][3];
void *func(void *arg)
{
    int id =(int)arg;
    int i,j;
    if(id<=1)
    {
    for(i=0;i<3;i++)
    for(j=0;j<3;j++)
    {
    if(id==0)
    add[i][j]=m1[i][j]+m2[i][j];
    if(id==1)
    sub[i][j]=m1[i][j]-m2[i][j];
    }
    }
    else
    {
    	for (i=0;i<3;i++)
    	for(j=0;j<3;j++)
    	{
    		mul[i][j]=m1[i][0]*m2[0][j]+m1[i][1]*m2[1][j]+m1[i][2]*m2[2][j];
    	}
    }
    //return ans;
}

int main()
{
	
    pthread_t t[3];//0 for add,1 for sub,2 for multiplication
    //int answer[3][3][3];
    printf("M1\n");
    for (int i=0;i<3;i++)
    {
    for (int j=0;j<3;j++)
    {
    m1[i][j]=3*i+j;
    m2[i][j]=3*i+j+1;
    printf("%d ",m1[i][j]);
    }
    printf("\n");
    }
    printf("M2\n");
    for (int i=0;i<3;i++)
    {
    for (int j=0;j<3;j++)
    {
    
    printf("%d ",m2[i][j]);
    }
    printf("\n");
    }
    for(int i=0;i<3;i++)
    {
    	
    	pthread_create(&t[i],NULL,&func,(void*)i);
    	
    }
   
   
    
    for(int i=0;i<3;i++)
    pthread_join(t[i],NULL);
    
    int sumi=0;
    int i,j;
    for(int id=0;id<3;id++)
    {
    if(id==0)
    printf(" Add ");
    if(id==1)
    printf(" Subtract ");
    if(id==2)
    printf(" Multiply");
    printf("\n");
    for(i=0;i<3;i++)
    {
    for(j=0;j<3;j++)
    {
    if(id==0)
    printf(" %d ",add[i][j]);
    if(id==1)
    printf(" %d ",sub[i][j]);
    if(id==2)
    printf(" %d ",mul[i][j]);
    
    
    }
    
    printf("\n");
    }
    }
    for(i=0;i<3;i++)
    {
    for(j=0;j<3;j++)
    {
    printf("");
    }
    printf("\n");
    }
    //printf("Sum is %d\n",sumi);
    
    

return 0;
}