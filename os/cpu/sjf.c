#include <stdio.h>

struct process {
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    int completed;
};

void main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    struct process p[n];
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter arrival time of process %d: ", i + 1);
        scanf("%d", &p[i].at);
        printf("Enter burst time of process %d: ", i + 1);
        scanf("%d", &p[i].bt);
        p[i].completed = 0;
    }
    int cur_time = 0, completed_processes = 0;
    while (completed_processes < n) {
        int shortest_index = -1;
        int shortest_bt = 100000;
        for (int i = 0; i < n; i++) {
            if (p[i].at <= cur_time && p[i].completed == 0) {
                if (p[i].bt < shortest_bt) {
                    shortest_bt = p[i].bt;
                    shortest_index = i;
                }
            }
        }
        if (shortest_index == -1) {
            cur_time++;
        } else {
            cur_time += p[shortest_index].bt;
            p[shortest_index].ct = cur_time;
            p[shortest_index].tat = p[shortest_index].ct - p[shortest_index].at;
            p[shortest_index].wt = p[shortest_index].tat - p[shortest_index].bt;
            p[shortest_index].completed = 1;
            completed_processes++;
        }
    }

    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", p[i].id, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }
}
