#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>

int main()
{
    pid_t pro;
    printf("Name - Swaraj \n Roll no. - CS21B2024 \n Insti- IIITDM\n");
    pro=fork();
    if(pro==0)
    {
        printf("This is the child process with pid = %d and parent pid = %d \n",getpid(),getppid());
        execl("./program32","./program32",NULL);
        printf("These are some random sentences that\n");
        printf("Should not be printed\n");
        
    }
    else
    {
        
        
        printf("This is the parent process with pid = %d and parent pid = %d \n",getpid(),getppid());
        
        
    }
    return 0;
}