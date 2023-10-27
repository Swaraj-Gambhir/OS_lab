#include<stdio.h>
#include<stdbool.h>
int max[6][4]={{5,4,4,3},
               {3,2,2,1},
               {1,2,1,0},
               {3,2,2,4},
               {1,2,2,2},
               {0,0,0,1}};
int allocation[6][4]={{3,1,1,0},
                     {1,1,1,1},
                     {1,0,0,0},
                     {2,2,2,2},
                     {1,0,0,0},
                     {0,0,0,0}};
int need[6][4];
int available[4]={4,4,2,2};
void computeneed()
{
    int i,j;
    for(i=0;i<6;i++)
    {
        for(j=0;j<4;j++)
        {
            need[i][j]=max[i][j]-allocation[i][j];
        }
    }
}
void print(int matrix[6][4])
{
   int i,j;
    for(i=0;i<6;i++)
    {
        for(j=0;j<4;j++)
        {
            printf(" %d ",matrix[i][j]);
        }
        printf("\n");
    } 
}
bool cond(int k,int array1[k],int array2[k])
{
    for (int i =0;i<k;i++)
    {
        if(array2[i]>array1[i])
        return false;
    }
    return true;
}
int*updatework(int work[4],int array[4])
{
    int i;
    for (i=0;i<4;i++)
    {
        work[i]=work[i]+array[i];
    }
    return work;
}
bool checkforalltrue(bool finish[6])
{
    int j;
    for(j=0;j<6;j++)
           {
               if(finish[j]==false)
               return false;
           }
        return true;
}
bool check_safe()
{
    bool finish[6]={false,false,false,false,false,false};
    int array[6];
    
    int work[4];
    int i,j;
    for(i=0;i<4;i++)
    {
         work[i]=available[i];
    }
    i=0;
    int k=0;
    int cycle=0;
    while(cycle<6)
    {
       if(finish[i]==false && cond(4,work,need[i]))
       {
           finish[i]=true;
           array[k++]=i;
           int *q;
           q=updatework(work,allocation[i]);
           *work=*q;
           cycle=0;
       }
       else
       {
           if(checkforalltrue(finish))
           {
               printf("It is in safe sequence\n");
               printf("%d %d %d %d %d %d\n",array[0],array[1],array[2],array[3],array[4],array[5]);
               return true;
               break;
           }
           else
           {
               i=(i+1)%6;
               cycle++;
           }
       }
    }
    return false;
}
void bankers(int request[4],int process)
{
    int i;
    if(cond(4,need[process],request))
    {
       if(cond(4,available,request))
       {
           for(i=0;i<4;i++)
           {
               available[i]=available[i]-request[i];
               allocation[process][i]=allocation[process][i]+request[i];
               need[process][i]=need[process][i]-request[i];
           }
           if(check_safe())
               {
                    printf("Request Accepted\n");
                   for(i=0;i<4;i++)
                    {
                        available[i]=available[i]+allocation[process][i];
                        allocation[process][i]=0;
                        need[process][i]=0;
                    }
               }
               else
               {
                   printf("Request Declined\n");
                   for(i=0;i<4;i++)
                    {
                        available[i]=available[i]+request[i];
                        allocation[process][i]=allocation[process][i]-request[i];
                        need[process][i]=need[process][i]+request[i];
                    }
               }
       }
       else
       {
           printf("Error\n");
       }
    }
    else
    {
        printf("Error\n");
    }
    
}
int main()
{
    computeneed();
    printf("Need Matrix\n");
    print(need);
    printf("\nAvailable %d %d %d %d\n",available[0],available[1],available[2],available[3]);
    check_safe();
    int request[4];
    int process;
    while(true)
    {
        printf("Enter 0 0 0 0 0 to quit\n");
        printf("Enter the process no.\n");
        scanf("%d",&process);
        for (int i=0;i<4;i++)
        {
            printf("Enter the request for resource no. %d\t",i+1);
            scanf("%d",&request[i]);
        }
        if(process==0 && request[0]==0 && request[1]==0 && request[2]==0 && request[3]==0)
        break;
        bankers(request,process);
        
    }
    return 0;
}