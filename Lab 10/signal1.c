//Swaraj
//CS21B2024
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>
#include<signal.h>
int i;
int a[8]= {2, 1, 3, 0, 5, 0, 7, 9};
void sighandler1(int signum)
{
	printf("Its a floating point error\n");
	sleep(1);
	raise(SIGKILL);
}
void sighandler2(int signum)
{
	printf("No. is greater than 20\n");
	exit(0);
}
void sighandler3(int signum)
{
	printf("In Sigusr2\n");
	a[i]=1;
	for (int j=0;j<8;j++)
	{
	 printf("%d ",a[j]);
	}
	printf("\n");
	
}
int main()
{
    int no;
    pid_t pro;
    pro=fork();
    if(pro!=0) 
    {
    	wait(NULL);
	//int a[8]= {2, 1, 3, 0, 5, 0, 7, 9};
	int no;
	printf("Enter a no.\n");
	scanf("%d",&no);
	

	signal(SIGFPE,sighandler1);
	signal(SIGUSR2,sighandler3);
	for (i=0;i<8;i++)
	{
		int y=1;
		y=no%a[i];
		sleep(1);
		printf("%d mod %d = %d\n",no,a[i],y);
	}
	
	
    }
    else 
    {
	srand(1000);
	signal(SIGUSR1,sighandler2);
	while(1)
	{
		int no=rand();
		no=10+no%20;
		printf("%d\n",no);
		if(no>=20);
		raise(SIGUSR1);
	}
    }
    return 0;
}