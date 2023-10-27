//Swaraj
//CS21B2024
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
int maxi(int*arr,int no) //Function to find maximum
{
    
    int max;
    max=0;
    for (int i=0;i<no;i++)
    {
        if(max<arr[i])
        max=arr[i];
        
    }
    no=max;
    return no;
}
int main()
{
    int no;
    printf("Enter no. of elements in the array\n"); //ACcepting the array
    scanf("%d",&no);
    int arr[no];
    printf("Enter the elements one by one\n");
    for (int i=0;i<no;i++)
    {
        printf("Enter the element on position %dth ",i );
        scanf("%d",&arr[i]);
        printf("\n");
    }
    int ma;
    ma=maxi(arr,no);
    printf("Maximum before calling any fork %d\n",ma);
    pid_t pro;
    pro=fork();
    if(pro==0)   //Child Process
    {
        printf("This is the child process with pid = %d and parent pid = %d \n",getpid(),getppid());
        for(int i=0;i<no;i++)
        {
            arr[i]+=2;
            printf("The %d th element is %d with address as %p\n",i,arr[i],&arr[i]);
            
        }
        printf("MAximum element is as follow %d\n",maxi(arr,no));
    }
    else //PArent process
    {
        wait(NULL);
        printf("This is the parent process with pid = %d and parent pid = %d \n",getpid(),getppid());
        for(int i=0;i<no;i++)
        {
            arr[i]-=3;
            printf("The %d th element is %d with address as %p\n",i,arr[i],&arr[i]);
            
        }
        printf("MAximum element is as follow %d\n",maxi(arr,no));
        
    }
    return 0;
}