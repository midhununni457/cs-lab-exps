
#include <stdio.h>

#define MAX_STATES 20
#define MAX_SYMBOLS 10

int main() {
    int n, num_sym, i, j, k, s;
    int trans[MAX_STATES][MAX_SYMBOLS];
    int final[MAX_STATES];
    int group[MAX_STATES];
    int rep[MAX_STATES];
    int count = 0;

    char symbols[MAX_SYMBOLS];

    printf("Enter number of states: ");
    scanf("%d", &n);

    printf("Enter number of input symbols: ");
    scanf("%d", &num_sym);

    printf("Enter input symbols: ");
    for(s = 0; s < num_sym; s++)
        scanf(" %c", &symbols[s]);

    // Read transition matrices
    for(s = 0; s < num_sym; s++) {
        printf("Enter transition matrix for symbol %c:\n", symbols[s]);

        for(i = 0; i < n; i++) {
            for(k = 0; k < n; k++) {
                int val;
                scanf("%d", &val);

                if(val == 1)
                    trans[i][s] = k;
            }
        }
    }

    // Read final states
    printf("Enter final states (0 for non-final, 1 for final):\n");
    for(i = 0; i < n; i++)
        scanf("%d", &final[i]);

    // Initialize all states as ungrouped
    for(i = 0; i < n; i++)
        group[i] = -1;

    // Find equivalent states
    for(i = 0; i < n; i++) {
        if(group[i] != -1)
            continue;

        group[i] = count;
        rep[count] = i;

        for(j = i + 1; j < n; j++) {
            if(final[i] != final[j])
                continue;

            int equiv = 1;

            for(k = 0; k < num_sym; k++) {
                if(final[trans[i][k]] != final[trans[j][k]]) {
                    equiv = 0;
                    break;
                }
            }

            if(equiv)
                group[j] = count;
        }

        count++;
    }

    // Display minimized DFA
    printf("\nMINIMIZED DFA\n\n");

    printf("%-10s %-20s", "State", "Original States");

    for(s = 0; s < num_sym; s++)
        printf("%-10c", symbols[s]);

    printf("%-10s\n", "Final");

    printf("----------------------------------------------------------\n");

    for(i = 0; i < count; i++) {
        char stateName[16];
        sprintf(stateName, "M%d", i);

        char origStates[64];
        int len = sprintf(origStates, "{");

        for(j = 0; j < n; j++) {
            if(group[j] == i)
                len += sprintf(origStates + len, "q%d ", j);
        }

        sprintf(origStates + len, "}");

        printf("%-10s %-20s", stateName, origStates);

        for(s = 0; s < num_sym; s++) {
            int dest = trans[rep[i]][s];
            char destName[16];
            sprintf(destName, "M%d", group[dest]);
            printf("%-10s", destName);
        }

        printf("%-10s\n", final[rep[i]] ? "Yes" : "No");
    }

    printf("\nInitial State: M%d\n", group[0]);

    printf("Final States: ");
    for(i = 0; i < count; i++) {
        if(final[rep[i]])
            printf("M%d ", i);
    }

    printf("\n");

    return 0;
}


/*
Sample Input:
Enter number of states: 4
Enter number of input symbols: 2
Enter input symbols: 0 1
Enter transition matrix for symbol 0:
0 1 0 0
0 1 0 0
0 0 0 1
0 0 0 1
Enter transition matrix for symbol 1:
0 0 1 0
0 0 1 0
0 0 0 1
0 0 0 1
Enter final states (0 for non-final, 1 for final):
0 0 1 1

Expected Output:
MINIMIZED DFA

State      Original States     0         1         Final
----------------------------------------------------------
M0         {q0 q1 }            M0        M1        No
M1         {q2 q3 }            M1        M1        Yes

Initial State: M0
Final States: M1
*/