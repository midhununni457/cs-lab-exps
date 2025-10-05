#include <stdio.h>

#define MAX_FRAMES 3

int frames[MAX_FRAMES];
int count[MAX_FRAMES];

void init() {
    for (int i=0; i<MAX_FRAMES; i++) {
        frames[i] = -1;
        count[i] = 0;
    }
}

void display() {
    for (int i=0; i<MAX_FRAMES; i++) {
        if (frames[i] != -1) {
            printf("%d", frames[i]);
        } else {
            printf("-");
        }
    }
    printf("\n");

    // ----displaying counter values-----
    // for (int i=0; i<MAX_FRAMES; i++) {
    //     printf("%d", count[i]);
    // }
    // printf("\n");
}

int findLFU() {
    int min = count[0];
    int lfu_frame = 0;

    for (int i=0; i<MAX_FRAMES; i++) {
        if (count[i] < min) {
            min = count[i];
            lfu_frame = i;
        }
    }
    return lfu_frame;
}

void lfu(int pages[], int n) {
    int page_fault = 0;
    
    for (int i=0; i<n; i++) {
        int page = pages[i];
        int found = 0;

        for (int j=0; j<MAX_FRAMES; j++) {
            if (frames[j] == page) {
                found = 1;
                count[j]++;
                printf("page %d found in frame %d\n", page, j);
                break;
            }
        }

        if (!found) {
            int lfu_frame = findLFU();
            frames[lfu_frame] = page;
            count[lfu_frame] = 1;
            page_fault++;
            printf("page %d loaded in frame %d\n", page, lfu_frame);
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
    lfu(pages, n);
}