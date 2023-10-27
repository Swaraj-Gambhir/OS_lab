//Swaraj
//CS21B2024
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main()
{
    int no;
    pid_t pro1,pro2,pro3,pro4;
    pro1=fork();
    pro4=1;
    if(pro1!=0)
    pro2=fork();
    if(pro1!=0 && pro2!=0)   //PArent process
    {
        wait(NULL);
        wait(NULL);
        printf("Parent Process my id is = %d and my parent pid = %d \n",getpid(),getppid());
    }
    else if(pro2==0 && pro1!=0)
    {
        pro3=fork();
        if(pro3!=0)
        pro4=fork();
        if(pro3!=0 && pro4!=0)
        {wait(NULL);
        wait(NULL);
        printf("Child 2 My id is %d and my parent id is  %d\n",getpid(),getppid());
        }
        
        if(pro3==0)
        printf("Child 3 My id is %d and my parent id is  %d\n",getpid(),getppid());
        if( pro4==0 )
        printf("Child 4 My id is %d and my parent id is  %d\n",getpid(),getppid());
    }
    else if(pro1==0)
    {
        printf("Child 1 My id is %d and my parent id is  %d\n",getpid(),getppid());
    }
    return 0;
}