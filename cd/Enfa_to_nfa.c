#include <stdio.h>

#define MAX_STATES 10
#define MAX_SYMBOLS 10

int n, num_sym;
int e[MAX_STATES][MAX_STATES];
int t[MAX_SYMBOLS][MAX_STATES][MAX_STATES];
int c[MAX_SYMBOLS][MAX_STATES][MAX_STATES];

void closure(int s, int vis[]) {
    vis[s] = 1;
    for (int i = 0; i < n; i++)
        if (e[s][i] && !vis[i])
            closure(i, vis);
}

int main() {
    printf("Enter number of states: ");
    scanf("%d", &n);

    printf("Enter number of input symbols: ");
    scanf("%d", &num_sym);

    printf("Enter epsilon transition matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &e[i][j]);

    for (int s = 0; s < num_sym; s++) {
        printf("Enter transition matrix for input symbol %d:\n", s);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                scanf("%d", &t[s][i][j]);
    }

    for (int s = 0; s < num_sym; s++) {
        for (int i = 0; i < n; i++) {
            int vis[MAX_STATES] = {0};
            closure(i, vis);

            for (int j = 0; j < n; j++)
                if (vis[j])
                    for (int k = 0; k < n; k++)
                        if (t[s][j][k])
                            c[s][i][k] = 1;
        }
    }

    for (int s = 0; s < num_sym; s++) {
        printf("\nNFA Transition Matrix for input symbol %d:\n", s);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++)
                printf("%d ", c[s][i][j]);
            printf("\n");
        }
    }

    return 0;
}

/*
Sample Input:
Enter number of states: 3
Enter number of input symbols: 2
Enter epsilon transition matrix:
0 1 0
0 0 1
0 0 0
Enter transition matrix for input symbol 0:
1 0 0
0 1 0
0 0 1
Enter transition matrix for input symbol 1:
0 0 0
0 0 1
1 0 0

Expected Output:
NFA Transition Matrix for input symbol 0:
1 1 1 
0 1 1 
0 0 1 

NFA Transition Matrix for input symbol 1:
1 0 1 
1 0 1 
1 0 0 
*/