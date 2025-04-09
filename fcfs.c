#include <stdio.h>

struct process {
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
};

void main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    struct process p[n];
    for (int i=0; i<n; i++) {
        int a, b;
        printf("Enter arrival time of process %d: ", i+1);
        scanf("%d", &a);
        printf("Enter burst time of process %d: ", i+1);
        scanf("%d", &b);
        p[i].at = a;
        p[i].bt = b;
    }
    int cur_time = 0, index = 0;
    for (int i=0; i<n-1; i++) {
        for (int j=0; j<n-i-1; j++) {
            if (p[j].at > p[j+1].at) {
                struct process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }
    for (int i=0; i<n; i++) {
        if (cur_time < p[i].at) {
            cur_time = p[i].at;
        }
        cur_time += p[i].bt;
        p[i].ct = cur_time;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
    }
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", i+1, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }

    // Display Gantt chart
    printf("\nGantt Chart:\n");

    // Print the top border of the Gantt chart
    printf(" ");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p[i].bt; j++) {
            printf("--");
        }
        printf(" ");
    }
    printf("\n|");

    // Print the process IDs in the Gantt chart
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p[i].bt; j++) {
            printf(" ");
        }
        printf("P%d", i + 1);
        for (int j = 0; j < p[i].bt; j++) {
            printf(" ");
        }
        printf("|");
    }
    printf("\n ");

    // Print the bottom border of the Gantt chart
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p[i].bt; j++) {
            printf("--");
        }
        printf(" ");
    }
    printf("\n0");

    // Print the completion times below the Gantt chart
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p[i].bt; j++) {
            printf("  ");
        }
        printf("%d", p[i].ct);
    }
    printf("\n");
}




