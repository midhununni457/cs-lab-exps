#include <stdio.h>

#define MAX_FRAMES 3 

int frames[MAX_FRAMES];
int rear = -1;

void init() {
    for (int i=0; i<MAX_FRAMES; i++) {
        frames[i] = -1;
    }
}

void display() {
    for (int i=0; i<MAX_FRAMES; i++) {
        if (frames[i] != -1) {
            printf("%d ", frames[i]);
        } else {
            printf("-");
        }
    }
    printf("\n");
}

void fifo(int pages[], int n) {
    int page_fault = 0;
    // int front = 0;

    for (int i=0; i<n; i++) {
        int page = pages[i];
        int found = 0;

        for (int j=0; j<MAX_FRAMES; j++) {
            if (frames[j] == page) {
                found = 1;
                printf("page %d already there at %d\n", page, j);
                break;
            }
        }

        if (!found) {
            rear = (rear + 1) % MAX_FRAMES;
            frames[rear] = page;
            page_fault++;
            printf("page %d loaded to frame %d\n", page, rear);
        }

        display();
    }
    printf("total page faults: %d\n", page_fault);
}

void main() {
    int n;
    printf("Enter no: of pages: ");
    scanf("%d", &n);
    int pages[n];
    printf("Enter page sequence: ");
    for (int i=0; i<n; i++) {
        scanf("%d", &pages[i]);
    }
    init();
    fifo(pages, n);
}