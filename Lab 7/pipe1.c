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
    pid_t pro;
    
    int pipe1[2],pipe2[2];
    int status;
    char msg[100];
    char rcv[100];
    status=pipe(pipe1);//Send message from parent to child
    if(status==-1)
    printf("Unable to create pipe\n");
    status=pipe(pipe2);
    if(status==-1)//pipe[0]-Read
    printf("Unable to create pipe\n");
    pro=fork();
    if(pro==0) 
    {
    	//sleep(5);
    	char rcv1[100];
        close(pipe1[1]);
      	close(pipe2[0]);
      	read(pipe1[0],rcv1,sizeof(rcv1));
        printf("Child Process my id is = %d and my parent pid = %d \n",getpid(),getppid());
        
      	
      	printf("This is a child process\nMessage from parent process is as follow\n%s\n",rcv1);
      	int i,j;
      	char temp;
      	int no;
      	no=strlen(rcv1);
      	j=no-1;
    	//printf("\n\n%c\n\n%d\n",rcv1[3],no);
    	char eer[100];
    	
        for (i=0;i<no;i++)
        {
            eer[i]=rcv1[j];
            j--;
        }
        //printf("\n\n%s\n\n",eer);
      	write(pipe2[1],eer,sizeof(rcv1));
    }
    else 
    {
        close(pipe1[0]);
      	close(pipe2[1]);
      	printf("Parent Process my id is = %d and my parent pid = %d \n",getpid(),getppid());
      	printf("Give input from parent\n");
      	scanf("%s",msg);
      	write(pipe1[1],msg,sizeof(msg));
      	read(pipe2[0],rcv,sizeof(rcv));
      	wait(NULL);
      	printf("Message from child is as follow\n%s\n",rcv);
      	
    }
    return 0;
}