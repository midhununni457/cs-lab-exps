#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int n, w, i = 1, j;

    printf("Enter number of frames: ");
    scanf("%d", &n);

    printf("Enter window size: ");
    scanf("%d", &w);

    srand(time(0)); // Random ACK simulation

    while (i <= n) {

        printf("\nSending frames: ");

        // Send frames within the window
        for (j = i; j < i + w && j <= n; j++) {
            printf("%d ", j);
        }

        printf("\n");

        // Simulate ACK reception
        for (j = i; j < i + w && j <= n; j++) {

            int ack = rand() % 2; // Generates 0 or 1 randomly

            if (ack == 1) {
                printf("ACK received for frame %d\n", j);
            }
            else {
                printf("ACK lost for frame %d\n", j);
                printf("Timeout! Retransmitting from frame %d\n", j);
                break;
            }
        }

        // Move window forward
        if (j == i + w || j > n) {
            i = j; // All ACKs received
        }
        else {
            i = j; // Retransmit from lost frame
        }
    }

    return 0;
}