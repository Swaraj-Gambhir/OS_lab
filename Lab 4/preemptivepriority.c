#include <stdio.h>
#include <stdlib.h>

typedef struct process 
{
    int PID;
    int AT;
    int PR;
    int BT;
    int CT;
    int TAT;
    int WT;
    int RT;
} process;

typedef struct node 
{
    process *data;
    struct node *next;
} node;

typedef struct queue 
{
    node *front;
    node *rear;
} queue;

queue *create_queue() 
{
    queue *q = malloc(sizeof(queue));
    q->front = NULL;
    q->rear = NULL;
    return q;
}

int is_empty(queue *q) 
{
    return q->front == NULL;
}

void enqueue(queue *q, process *p) 
{
    node *new_node = malloc(sizeof(node));
    new_node->data = p;
    new_node->next = NULL;

    if (is_empty(q)) 
    {
        q->front = new_node;
        q->rear = new_node;
    } 
    else 
    {
        q->rear->next = new_node;
        q->rear = new_node;
    }
}

process *dequeue(queue *q) 
{
    if (is_empty(q)) 
    {
        return NULL;
    }

    node *temp = q->front;
    process *p = temp->data;

    q->front = q->front->next;

    if (q->front == NULL) 
    {
        q->rear = NULL;
    }

    free(temp);

    return p;
}

void preemptive_priority_scheduling(process *processes, int n) 
{
    queue *q = create_queue();

    for (int i = 0; i < n; i++) 
    {
        enqueue(q, &processes[i]);
    }

    int time = 0;

    while (!is_empty(q)) 
    {
        process *highest_priority_process = NULL;

        for (node *temp = q->front; temp != NULL; temp = temp->next) 
        {
            if (temp->data->AT <= time && temp->data->BT > 0) 
            {
                if (highest_priority_process == NULL || temp->data->PR < highest_priority_process->PR) 
                {
                    highest_priority_process = temp->data;
                }
            }
        }

        if (highest_priority_process != NULL) 
        {
            highest_priority_process->BT--;
            time++;

            if (highest_priority_process->BT == 0) 
            {
                highest_priority_process->CT = time;
                highest_priority_process->TAT = highest_priority_process->CT - highest_priority_process->AT;
                highest_priority_process->WT = highest_priority_process->TAT - highest_priority_process->BT;
                highest_priority_process->RT = highest_priority_process->WT;

                dequeue(q);
            }
        } 
        else 
        {
            time++;
        }
    }

}

int main() 
{
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    process *processes = malloc(n * sizeof(process));

    for (int i = 0; i < n; i++) 
    {
        printf("Enter the details for process %d:\n", i + 1);
        printf("Process ID: ");
        scanf("%d", &processes[i].PID);
        printf("Arrival Time: ");
        scanf("%d", &processes[i].AT);
        printf("Priority: ");
        scanf("%d", &processes[i].PR);
        printf("Burst Time: ");
        scanf("%d", &processes[i].BT);
        printf("\n");
    }

    preemptive_priority_scheduling(processes, n);

    double avg_TAT = 0.0;
    double avg_WT = 0.0;
    double avg_RT = 0.0;

    for (int i = 0; i < n; i++) 
    {
        avg_TAT += processes[i].TAT;
        avg_WT += processes[i].WT;
        avg_RT += processes[i].RT;

        printf("Process %d:\n", processes[i].PID);
        printf("Completion Time: %d\n", processes[i].CT);
        printf("Turnaround Time: %d\n", processes[i].TAT);
        printf("Waiting Time: %d\n", processes[i].WT);
        printf("Response Time: %d\n", processes[i].RT);
        printf("\n");
    }

    printf("\n");
    printf("Average Turnaround Time: %.2lf\n", avg_TAT/n);
    printf("Average Waiting Time: %.2lf\n", avg_WT/n);
    printf("Average Response Time: %.2lf\n", avg_RT/n);

    free(processes);

    return 0;
}
