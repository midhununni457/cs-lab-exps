#include <stdio.h>

struct process {
    int id;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
};

struct process queue[100];
int front = 0, rear = -1;

void main() {
    int n;
    printf("Enter no: of processes: ");
    scanf("%d", &n);
    struct process p[n];
    for (int i=0; i<n; i++) {
        int a, b;
        printf("Enter arrival time of process %d: ", i+1);
        scanf("%d", &a);
        printf("Enter burst time of process %d: ", i+1);
        scanf("%d", &b);
        p[i].id = i+1;
        p[i].at = a;
        p[i].bt = b;
        p[i].ct = 0;
        p[i].tat = 0;
        p[i].wt = 0;
    }
    int tq, cur_time = 0, completed = 0;
    printf("Enter time quantum: ");
    scanf("%d", &tq);
    while (completed < n) {
        for (int i=0; i<n; i++) {
            if (p[i].at <= cur_time && p[i].at > cur_time-tq) {
                queue[++rear] = p[i];
            }
        }
        if (front > rear) {
            cur_time++;
            continue;
        }
        if (queue[front].bt <= tq) {
            cur_time += queue[front].bt;
            for (int i=0; i<n; i++) {
                if (p[i].id == queue[front].id) {
                    p[i].ct = cur_time;
                    p[i].tat = p[i].ct - p[i].at;
                    p[i].wt = p[i].tat - p[i].bt;
                }
            }
            completed++;
            front++;
        } else {
            cur_time += tq;
            queue[++rear] = queue[front];
            queue[rear].bt -= tq;
            front++;
        }
    }
    int tot_tat = 0, tot_wt = 0;
    printf("Process\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i=0; i<n; i++) {
        tot_tat += p[i].tat;
        tot_wt += p[i].wt;
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", i+1, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }
    printf("Avg TAT: %.2f\nAvg WT: %.2f\n", (float)tot_tat/n, (float)tot_wt/n);
}