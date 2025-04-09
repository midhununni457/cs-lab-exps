#include <stdio.h>

struct Process {
    int pid;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    int priority;
}

void priority(struct Process proc[], int n) {
    int cur_time = 0, completed = 0;

    while (completed < n) {
        int idx = -1;
        int highest_priority = 100;

        for (int i = 0; i < n; i++) {
            if (proc[i].at <= cur_time && proc[i].ct == 0 && proc[i].priority < highest_priority) {
                highest_priority = proc[i].priority;
                idx = i;
            }
        }

        if (idx != -1) {
            proc[idx].ct = cur_time + proc[idx].bt;
            proc[idx].tat = proc[idx].ct - proc[idx].at;
            proc[idx].wt = proc[idx].tat - proc[idx].bt;
            completed++;
            cur_time += proc[idx].bt;
        } else {
            cur_time++;
        }
    }
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];

    printf("Enter process details (at, bt, priority):\n");
    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("P%d: ", i + 1);
        scanf("%d %d %d", &proc[i].at, &proc[i].bt, &proc[i].priority);
    }

    priority(proc, n);

    float awt = 0, atat = 0;
    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].at,
               proc[i].bt, proc[i].ct, proc[i].priority, proc[i].wt, proc[i].tat);
        awt += proc[i].wt;
        atat += proc[i].tat;
    }
    printf("Avg WT=%f\t Avg TAT=%f", awt / n, atat / n);
    return 0;
}
