#include <stdio.h>
#include <stdlib.h>

#define MAX_STATES 10
#define MAX_SYMBOLS 10
#define MAX_SUBSETS 1024

void main() {
    int n, s;
    int trans[MAX_STATES][MAX_SYMBOLS][MAX_STATES];
    int final[MAX_STATES];
    int queue[MAX_SUBSETS], seen[MAX_SUBSETS] = {0};
    int front = 0, rear = 0;

    printf("Enter no: of states: ");
    scanf("%d", &n);
    printf("Enter no: of symbols: ");
    scanf("%d", &s);

    for (int i = 0; i<n; i++) {
        for (int j=0; j<s; j++) {
            printf("Enter transitions from state %d using symbol %d: ", i, j);
            for (int k=0; k<n; k++) {
                scanf("%d", &trans[i][j][k]);
            }
        }
    }

    for (int i=0; i<n; i++) {
        printf("Is state %d final(0=no, 1=yes): ", i);
        scanf("%d", &final[i]);
    }

    // enqueue q0 to queue & mark subset 1 as seen
    queue[rear++] = 1;
    seen[1] = 1;

    while (front < rear) {
        int cur = queue[front++];
        printf("DFA State %d {", cur);
        for (int i=0; i<n; i++) {
            if (cur & (1 << i))
                printf("q%d ", i);
        }
        printf("}\n");

        // check next dfa state for each symbol
        for (int j=0; j<s; j++) {
            int next = 0;
            for (int i=0; i<n; i++) {
                if (cur & (1 << i)) {
                    for (int k=0; k<n; k++) {
                        if (trans[i][j][k])
                            next |= (1<<k);
                    }
                }
            }
            printf("Input %d -> %d", j, next);
            
            if (!seen[next]) {
                queue[rear++] = next;
                seen[next] = 1;
            }
            printf("\n");
        }
    }
}

/*
Sample input:
Enter no: of states: 3
Enter no: of symbols: 2
Enter transitions from state 0 using symbol 0: 1 1 0
Enter transitions from state 0 using symbol 1: 1 0 0
Enter transitions from state 1 using symbol 0: 0 0 0
Enter transitions from state 1 using symbol 1: 0 0 1
Enter transitions from state 2 using symbol 0: 0 0 0
Enter transitions from state 2 using symbol 1: 0 0 0
Is state 0 final(0=no, 1=yes): 0 
Is state 1 final(0=no, 1=yes): 0
Is state 2 final(0=no, 1=yes): 1

Sample output:
DFA State 1 {q0 }
Input 0 -> 3
Input 1 -> 1
DFA State 3 {q0 q1 }
Input 0 -> 3
Input 1 -> 5
DFA State 5 {q0 q2 }
Input 0 -> 3
Input 1 -> 1
*/

