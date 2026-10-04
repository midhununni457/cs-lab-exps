#include <stdio.h>
#define MAX 20

int main() {
    int n, i, j;
    int trans[MAX][2];
    int final[MAX];

    printf("Enter number of states: ");
    scanf("%d", &n);

    printf("Enter transition table (for 0 and 1):\n");
    for(i = 0; i < n; i++)
        scanf("%d %d", &trans[i][0], &trans[i][1]);

    printf("Enter final states (0 for non-final, 1 for final):\n");
    for(i = 0; i < n; i++)
        scanf("%d", &final[i]);

    printf("\nEquivalent states are:\n");

    for(i = 0; i < n; i++) {
        for(j = i + 1; j < n; j++) {

            if(final[i] == final[j] &&
               final[trans[i][0]] == final[trans[j][0]] &&
               final[trans[i][1]] == final[trans[j][1]]) {

                printf("q%d and q%d\n", i, j);
            }
        }
    }

    return 0;
}

/*
Sample Input:
Enter number of states: 4
Enter transition table (for 0 and 1):
1 2
1 2
3 3
3 3
Enter final states (0 for non-final, 1 for final):
0 0 1 1

Expected Output:
Equivalent states are:
q0 and q1
q2 and q3
*/