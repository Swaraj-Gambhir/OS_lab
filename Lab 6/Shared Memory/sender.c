#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/shm.h>
#define SHMSIZE 250
int main()
{
char c; int shmid; key_t key; char *shm,*s;
key=6969;
//Create the segment
if((shmid=shmget(key,SHMSIZE,IPC_CREAT|0666))<0)
{
printf("Error\n");
exit(1);
}
//Attaching memory
if((shm=shmat(shmid,NULL,0))==(char*)-1)
{
printf("Error\n");
exit(1);
}
s=shm;
*s++='!';
int len;
printf("Enter no. of char present in input\n");
scanf("%d",&len);
char a[len];
printf("Enter the string\n");
scanf("%s",a);
for (int i=0;i<len;i++)
{*s++=a[i];}

*s=0;
 
 while(*shm!='#')
 	sleep(1);

printf("Entering Recieve Mode\n");

while(*shm!='+')
 	sleep(1);

printf("The string is \n");
++shm;
for (s=shm;*s!=0;s++)
putchar(*s);

putchar('\n');
--shm;

*shm='@';

 
 exit(0);




}