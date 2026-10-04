#include <stdio.h>

#define MAX_STATES 10
#define MAX_SYMBOLS 10
#define MAX_SUBSETS 1024

int n, num_sym;
int trans[MAX_STATES][MAX_SYMBOLS][MAX_STATES];
int visited[MAX_SUBSETS];
int queue[MAX_SUBSETS];
int front = 0, rear = 0;

int main() {
    int i, j, k, s;

    printf("Enter number of states: ");
    scanf("%d", &n);

    printf("Enter number of input symbols: ");
    scanf("%d", &num_sym);

    for (s = 0; s < num_sym; s++) {
        printf("Enter transition matrix for input symbol %d:\n", s);
        for (i = 0; i < n; i++)
            for (k = 0; k < n; k++)
                scanf("%d", &trans[i][s][k]);
    }

    queue[rear++] = 1;      // Start state = {q0} (bit 0 set)

    while(front < rear) {
        int current = queue[front++];

        if(visited[current])
            continue;

        visited[current] = 1;

        printf("\nSubset %d\n", current);

        for(j = 0; j < num_sym; j++) {
            int next = 0;

            for(i = 0; i < n; i++) {
                if(current & (1 << i)) {
                    for(k = 0; k < n; k++) {
                        if(trans[i][j][k])
                            next |= (1 << k);
                    }
                }
            }

            printf("Input %d -> %d\n", j, next);

            if(!visited[next])
                queue[rear++] = next;
        }
    }

    return 0;
}

/*
Sample Input:
Enter number of states: 3
Enter number of input symbols: 2
Enter transition matrix for input symbol 0:
0 1 0
0 1 0
0 0 0
Enter transition matrix for input symbol 1:
0 0 1
0 0 0
0 0 1

Expected Output:
Subset 1
Input 0 -> 2
Input 1 -> 4

Subset 2
Input 0 -> 2
Input 1 -> 0

Subset 4
Input 0 -> 0
Input 1 -> 4

Subset 0
Input 0 -> 0
Input 1 -> 0
*/