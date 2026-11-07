
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
    int final[MAX_STATES] = {0};
    int num_final, state;

    printf("Enter number of states: ");
    scanf("%d", &n);

    printf("Enter number of input symbols: ");
    scanf("%d", &num_sym);

    char symbols[MAX_SYMBOLS];

    printf("Enter input symbols: ");
    for (i = 0; i < num_sym; i++)
        scanf(" %c", &symbols[i]);

    // Read transition matrices
    for (s = 0; s < num_sym; s++) {
        printf("\nEnter transition matrix for symbol %c:\n",
               symbols[s]);

        for (i = 0; i < n; i++)
            for (k = 0; k < n; k++)
                scanf("%d", &trans[i][s][k]);
    }

    // Read final states
    printf("\nEnter number of final states: ");
    scanf("%d", &num_final);

    printf("Enter final state numbers: ");
    for (i = 0; i < num_final; i++) {
        scanf("%d", &state);
        final[state] = 1;
    }

    // Initial DFA state = {q0}
    queue[rear++] = 1;
    visited[1] = 1;

    int dfa[MAX_SUBSETS][MAX_SYMBOLS];
    int dfaStates[MAX_SUBSETS];
    int count = 0;

    // Subset construction using BFS
    while (front < rear) {
        int current = queue[front++];

        dfaStates[count] = current;

        for (j = 0; j < num_sym; j++) {
            int next = 0;

            for (i = 0; i < n; i++) {
                if (current & (1 << i)) {
                    for (k = 0; k < n; k++) {
                        if (trans[i][j][k])
                            next |= (1 << k);
                    }
                }
            }

            dfa[count][j] = next;

            if (!visited[next]) {
                visited[next] = 1;
                queue[rear++] = next;
            }
        }

        count++;
    }

    // Display DFA transition table
    printf("\nDFA TRANSITION TABLE\n\n");

    printf("%-10s %-20s", "DFA State", "NFA Subset");

    for (j = 0; j < num_sym; j++)
        printf("%-12c", symbols[j]);

    printf("%-10s\n", "Final");

    printf("---------------------------------------------------------------\n");

    for (i = 0; i < count; i++) {
        int subset = dfaStates[i];
        int isFinal = 0;

        char dfaName[16];
        sprintf(dfaName, "D%d", i);

        char subStr[64];
        int len = sprintf(subStr, "{");

        for (j = 0; j < n; j++) {
            if (subset & (1 << j)) {
                len += sprintf(subStr + len, "q%d ", j);

                if (final[j])
                    isFinal = 1;
            }
        }

        sprintf(subStr + len, "}");

        printf("%-10s %-20s", dfaName, subStr);

        for (j = 0; j < num_sym; j++) {
            int dest = dfa[i][j];
            int d;

            for (d = 0; d < count; d++) {
                if (dfaStates[d] == dest)
                    break;
            }

            char destName[16];
            sprintf(destName, "D%d", d);
            printf("%-12s", destName);
        }

        printf("%-10s\n", isFinal ? "Yes" : "No");
    }

    printf("\nInitial DFA State: D0\n");

    printf("Final DFA States: ");
    for (i = 0; i < count; i++) {
        for (j = 0; j < n; j++) {
            if ((dfaStates[i] & (1 << j)) && final[j]) {
                printf("D%d ", i);
                break;
            }
        }
    }

    printf("\n");

    return 0;
}


/*
Sample Input:
Enter number of states: 3
Enter number of input symbols: 2
Enter input symbols: 0 1
Enter transition matrix for symbol 0:
1 1 0
1 0 0
0 0 0
Enter transition matrix for symbol 1:
0 0 1
0 1 0
1 1 0
Enter number of final states: 1
Enter final state numbers: 2

Expected Output:
DFA TRANSITION TABLE

DFA State  NFA Subset          0           1           Final
---------------------------------------------------------------
D0         {q0 }               D1          D2          No
D1         {q0 q1 }            D1          D3          No
D2         {q2 }               D4          D1          Yes
D3         {q1 q2 }            D0          D1          Yes
D4         {}                  D4          D4          No

Initial DFA State: D0
Final DFA States: D2 D3
*/