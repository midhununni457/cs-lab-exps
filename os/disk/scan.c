#include <stdio.h>
#include <stdlib.h>

#define MAX_TRACK 99

int scan(int requests[], int n, int head) {
    int total_seek_time = 0;

    for (int i=0; i<n; i++) {
        for (int j=0; j<n-i-1; j++) {
            if (requests[j+1] < requests[j]) {
                int temp = requests[j];
                requests[j] = requests[j+1];
                requests[j+1] = temp;
            }
        }
    }

    if (head < requests[0]) {
        total_seek_time += MAX_TRACK - head;
    } else {
        total_seek_time += MAX_TRACK - head;
        total_seek_time += MAX_TRACK - requests[0];
    }

    return total_seek_time;
}

void main() {
    int n, head;
    printf("Enter the number of requests: ");
    scanf("%d", &n);
    int requests[n];
    printf("Enter the requests: ");
    for (int i=0; i<n; i++) {
        scanf("%d", &requests[i]);
    }
    printf("Enter the initial head position: ");
    scanf("%d", &head);
    int total_seek_time = scan(requests, n, head);
    printf("Total seek time: %d\n", total_seek_time);
}