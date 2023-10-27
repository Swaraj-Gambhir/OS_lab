#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>

int main()
{
    pid_t pro;
    pro=fork();
    if(pro==0)
    {
        printf("This is the child process with pid = %d and parent pid = %d \n",getpid(),getppid());
        int no;
        printf("Enter no. of elements in the array\n");
        scanf("%d",&no);
        int*arr=(int*)malloc(sizeof(int)*no);
        printf("Enter the elements one by one\n");
        for (int i=0;i<no;i++) //Input
        {
            printf("Enter the element on position %dth ",i );
            scanf("%d",&arr[i]);
            printf("\n");
        }
        int key,i,j;
        for (i = 1; i < no; i++) //Insertion sort
        {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key)
            {
                arr[j + 1] = arr[j];
                j = j - 1;
            }
            arr[j + 1] = key;
        }
        for (i=0;i<no;i++)
        {
            printf("The %d th element is %d with address as %p\n",i,arr[i],&arr[i]);
        }
        
    }
    else
    {
        wait(NULL);
        printf("This is the parent process with pid = %d and parent pid = %d \n",getpid(),getppid());
        int no,i;
        printf("Enter no. of elements in the array\n");//Input
        scanf("%d",&no);
        int*arr=(int*)malloc(sizeof(int)*no);
        printf("Enter the elements one by one\n");
        for (int i=0;i<no;i++)
        {
            printf("Enter the element on position %dth ",i );
            scanf("%d",&arr[i]);
            printf("\n");
        }
        for (i=no-1;i>=0;i--)//REversing array
        {
            printf("The %d th element is %d with address as %p\n",i,arr[i],&arr[i]);
        }
        
        
    }
    return 0;
}