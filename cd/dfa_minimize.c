#include <stdio.h>

#define MAX_STATES 20
#define MAX_SYMBOLS 10

int main() {
    int n, num_sym, i, j, k, s;
    int trans[MAX_STATES][MAX_SYMBOLS];
    int final[MAX_STATES];

    printf("Enter number of states: ");
    scanf("%d", &n);

    printf("Enter number of input symbols: ");
    scanf("%d", &num_sym);

    for(s = 0; s < num_sym; s++) {
        printf("Enter transition matrix for input symbol %d:\n", s);
        for(i = 0; i < n; i++) {
            for(k = 0; k < n; k++) {
                int val;
                scanf("%d", &val);
                if(val == 1)
                    trans[i][s] = k;
            }
        }
    }

    printf("Enter final states (0 for non-final, 1 for final):\n");
    for(i = 0; i < n; i++)
        scanf("%d", &final[i]);

    printf("\nEquivalent states are:\n");

    for(i = 0; i < n; i++) {
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

            if(equiv) {
                printf("q%d and q%d\n", i, j);
            }
        }
    }

    return 0;
}

/*
Sample Input:
Enter number of states: 4
Enter number of input symbols: 2
Enter transition matrix for input symbol 0:
0 1 0 0
0 1 0 0
0 0 0 1
0 0 0 1
Enter transition matrix for input symbol 1:
0 0 1 0
0 0 1 0
0 0 0 1
0 0 0 1
Enter final states (0 for non-final, 1 for final):
0 0 1 1

Expected Output:
Equivalent states are:
q0 and q1
q2 and q3
*/