#include <stdio.h>
#include <stdlib.h>

// #define MAX_REQUESTS 20

int fcfs_disk(int requests[], int n, int pos) {
    int total_seek_time = 0;
    int cur_pos = pos;

    for (int i=0; i<n; i++) {
        total_seek_time += abs(cur_pos - requests[i]);
        cur_pos = requests[i];
    }

    return total_seek_time;
}

void main() {
    int n;
    printf("Enter number of requests: ");
    scanf("%d", &n);
    int requests[n];
    for (int i=0; i<n; i++) {
        printf("Enter request %d: ", i+1);
        scanf("%d", &requests[i]);
    }
    int pos;
    printf("Enter starting position of head: ");
    scanf("%d", &pos);
    int total_seek_time = fcfs_disk(requests, n, pos);
    printf("Total seek time: %d\n", total_seek_time);
}