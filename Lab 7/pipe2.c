//Swaraj
//CS21B2024
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>
int main()
{
    int no;
    pid_t pro,pro1;
    
    int pipe1[2],pipe2[2];
    int status;
    char msg[100];
    char rcv1[100];
    char rcv2[100];
    status=pipe(pipe1);//Send message from parent to child
    if(status==-1)
    printf("Unable to create pipe\n");
    
    pro=fork();
    if(pro==0) 
    {
      	status=pipe(pipe2);
    	if(status==-1)//pipe[0]-Read
    	printf("Unable to create pipe\n");
        
      	pro1=fork();
      	if(pro1==0)
      	{
      	sleep(5);
      	printf("GrandChild Process my id is = %d and my parent pid = %d \n",getpid(),getppid());
      	close(pipe2[0]);
      	
      	
      	printf("Give input from GrandChildren\n");
      	scanf("%s",msg);
      	write(pipe2[1],msg,sizeof(msg));
      	}
      	else
      	{
      	close(pipe1[1]);
      	close(pipe2[1]);
      	read(pipe1[0],rcv1,sizeof(rcv1));
        printf("Child Process my id is = %d and my parent pid = %d \n",getpid(),getppid());
        
      	
      	printf("\nMessage from parent process is as follow\n%s\n",rcv1);
      	int no1=strlen(rcv1);
      	read(pipe2[0],rcv2,sizeof(rcv2));
      	int no2=strlen(rcv2);
      	
      	printf("\nMessage from grandchildren process is as follow\n%s\n",rcv2);
    	//printf("\n\n%c\n\n%d\n",rcv1[3],no);

      	printf("%d   %d  \n",no1,no2);
      	
      	printf("Difference in message is as follow %d\n",no1-no2);
      	}
      	
    }
    else 
    {
        close(pipe1[0]);
      	
      	printf("Parent Process my id is = %d and my parent pid = %d \n",getpid(),getppid());
      	printf("Give input from parent\n");
      	scanf("%s",msg);
      	write(pipe1[1],msg,sizeof(msg));
      	    	
      	
      	wait(NULL);
    }
    return 0;
}