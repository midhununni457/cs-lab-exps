#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int name;
    int arrival;
    int burst;
    int remaining;
    int status;
    int completion;
    int waiting;
    int turnaround;
} Process;

typedef struct Node {
    Process process;
    struct Node* next;
} Node;
Node *front=NULL;
Node *rear=NULL;

void enqueue(Process process) {
    Node* newNode = (Node*)malloc(sizeof(Node));
 
    newNode->process = process;
    newNode->next = NULL;

    if (front == NULL) {
        front=rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
}

Process dequeue() {
   
    Node* temp = front;
    Process process = temp->process;
    front = front->next;
    free(temp);
    return process;
}
void printqueue()
{
    Node *temp=front;
    while(temp!=NULL)
    {
        printf("%d-->",temp->process.name);
        temp=temp->next;
        
    }
    printf("NULL\n");
}
int main() {
    Process processes[] = {
        {1, 0, 5, 5,0,-1,-1,-1},  
        {2, 1, 6, 6,0,-1,-1,-1},  
        {3, 2, 3, 3,0,-1,-1,-1},
        {4, 3, 1, 1,0,-1,-1,-1},  
        {5, 4, 5, 5,0,-1,-1,-1},  
        {6, 6, 4, 4,0,-1,-1,-1}
        
    };
    int n = sizeof(processes) / sizeof(Process);

    int quantum = 4;

    int currenttime = 0;
    int completed = 0;
   
    printf("Time  |  Process\n");
    printf("------+-------------------\n");

     enqueue(processes[0]);
     processes[0].status=1;
    while (completed < n ) {
        if (front != NULL) {
            Process currentProcess = dequeue();
            int execution_time = (currentProcess.remaining < quantum) ? currentProcess.remaining : quantum;
            currentProcess.remaining -= execution_time;
            currenttime += execution_time;
            for (int i = 0; i < n; i++) {
            if (processes[i].arrival <= currenttime && processes[i].status!=1) {
                enqueue(processes[i]);
                processes[i].status=1;
            }
        }
            printf("%-5d |  P%d\n", currenttime, currentProcess.name);
            if (currentProcess.remaining <= 0) {
                completed++;
                for(int i=0;i<n;i++) if (processes[i].name==currentProcess.name)
                           {processes[i].completion=currenttime;break;}
            } else {
                currentProcess.status=1;
                enqueue(currentProcess);
            }
        } else {
            currenttime++;
        }
    }

    float avwt=0.0;
    float avtat=0.0;
    printf("Process ArrivalTime BurstTime  CompletionTime  TurnAroundTime WaitingTime\n");
    for(int i=0;i<n;i++)
    {
    processes[i].turnaround=processes[i].completion-processes[i].arrival;
    processes[i].waiting=processes[i].turnaround-processes[i].burst;
    printf("P%d%10d%10d%20d%10d%20d\n",processes[i].name,processes[i].arrival,processes[i].burst,processes[i].completion,processes[i].turnaround,processes[i].waiting);
    avwt=avwt+processes[i].waiting;
    avtat=avtat+processes[i].turnaround;
    }
    printf("Average Waiting Time=%f\n",avwt/n);
    printf("Average Turn Around Time=%f\n",avtat/n);
      return 0;  
}