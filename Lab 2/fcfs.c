//Swaraj CS21B2024
#include<stdio.h>
#include<stdlib.h>
//global int  et;
struct process
{
    struct process* head;
    int P_id;
    int AT;
    int BT;
    struct process* tail;
};
/*struct process* updateprocess(struct process*Head)
{
    struct process* temp;
    temp=Head;
    int flag=0;
    int pat;
    while(temp->tail!=NULL)
    {
        if(flag==0)
        {
           pat=temp->AT;
        }
        
    }
    return NULL;
}*/
void display(struct process*Head)
{
    struct process* temp;
    temp=Head;
    do
    {
        printf("P_id=%d\n",temp->P_id);
        printf("AT=%d\n",temp->AT);
        printf("BT=%d\n",temp->BT);
        printf("\n");
        temp=temp->tail;
    }
    while(temp!=NULL);
    
}
int* completiontime(struct process* Head,int*ft)
{
    struct process*temp;
    temp=Head;
    int count=0;
    int time_elapsed,flag=0,diff;
    do
    {
        if(flag==0)
        {
            flag=1;
            time_elapsed=temp->AT;
            time_elapsed+=temp->BT;
            ft[count]=time_elapsed;
            count+=1;
        }
        else if(flag==1)
        {
            if(time_elapsed>=temp->AT)
            {
                time_elapsed+=temp->BT;
                printf("Time Elapsed %d\n",time_elapsed);
            }
            else
            {
                time_elapsed=temp->AT;
                time_elapsed+=temp->BT;
                printf("Time Elapsed %d\n",time_elapsed);
            }
            ft[count]=time_elapsed;
            count+=1;
        }
        
        temp=temp->tail;
    }
    while(temp!=NULL);
    return ft;
}
int* turnaroundtime(struct process* Head,int*tat)
{
    struct process*temp;
    temp=Head;
    int time_elapsed,flag=0,diff;
    int count=0;
    printf("Turnaround Time\n");
    do
    {
        if(flag==0)
        {
            flag=1;
            time_elapsed=temp->AT;
            time_elapsed+=temp->BT;
            
            
        }
        else if(flag==1)
        {
            if(time_elapsed>=temp->AT)
            {
                time_elapsed+=temp->BT;
              //  printf("Time Elapsed %d",time_elapsed);
            }
            else
            {
                time_elapsed=temp->AT;
                time_elapsed+=temp->BT;
                //printf("Time Elapsed %d",time_elapsed);
            }
        }
        printf("%d = %d\n",temp->P_id,time_elapsed-temp->AT);
        tat[count]=time_elapsed-temp->AT;
        count+=1;
        temp=temp->tail;
    }
    while(temp!=NULL);
    return tat;
}
int* waitingtime(struct process* Head,int*wt)
{
    struct process*temp;
    temp=Head;
    int time_elapsed,flag=0,diff;
    int count=0;
    printf("Waiting Time\n");
    do
    {
        if(flag==0)
        {
            flag=1;
            time_elapsed=temp->AT;
            time_elapsed+=temp->BT;
            wt[count]=temp->AT;
            count+=1;
            
        }
        else if(flag==1)
        {
            if(time_elapsed>=temp->AT)
            {
                wt[count]=time_elapsed-temp->AT;
                count+=1;
                time_elapsed+=temp->BT;
                
              //  printf("Time Elapsed %d",time_elapsed);
            }
            else
            {
                time_elapsed=temp->AT;
                time_elapsed+=temp->BT;
                wt[count]=0;
                count+=1;
                //printf("Time Elapsed %d",time_elapsed);
            }
        }
        printf("%d = %d\n",temp->P_id,wt[count-1]);
        
        temp=temp->tail;
    }
    while(temp!=NULL);
    return wt;
}
int main()
{
    int no;
    printf("Enter the no. of processes\n");
    scanf("%d",&no);
    struct process* prev;
    struct process* Head;
    int temp;
    prev=NULL;
    for (int i=0;i<no;i++)
    {
        struct process*p=( struct process*)malloc(sizeof(struct process));
        p->head=prev;
        if(i==0)
        Head=p;
        printf("Enter the process id\n");
        scanf("%d",&temp);
        p->P_id=temp;
        printf("Enter the Arrival Time\n");
        scanf("%d",&temp);
        p->AT=temp;
        printf("Enter the Burst Time\n");
        scanf("%d",&temp);
        p->BT=temp;
        p->tail=NULL;
        if(i!=0)
        prev->tail=p;
        prev=p;
       // Head=updateprocess(Head);
    }
    int *ft,*tat,*wt;
    ft=malloc(sizeof(no));
    tat=malloc(sizeof(no));
    wt=malloc(sizeof(no));
    display(Head);
    //printf("Completion Time=%d\n",completiontime(Head));
    ft=completiontime(Head,ft);
    int avg_tat=0,avg_wt=0;
    tat=turnaroundtime(Head,tat);
    wt=waitingtime(Head,wt);
    printf("P_id\tAT\tBT\tFT\tTAT\tWT\tRT\n");
    struct process*temp1;
    temp1=Head;
    for (int i=0;i<no;i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",temp1->P_id,temp1->AT,temp1->BT,ft[i],tat[i],wt[i],wt[i]);
        avg_tat+=tat[i];
        avg_wt+=wt[i];
        temp1=temp1->tail;
    }
    printf("Completion Time=%d\n",ft[no-1]);
    float a,b;
    a=(float)avg_tat;
    b=(float)avg_wt;
    a=a/no;
    b=b/no;
    printf("Average Turnaround Time=%f\n",a);
    printf("Average Waiting Time=%f\n",b);
    return 0;
}