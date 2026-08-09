#include <stdio.h>

#define MAX 10

int n;
int e[MAX][MAX], t[MAX][MAX], c[MAX][MAX];

void closure(int s, int vis[]) {
    vis[s] = 1;
    for (int i = 0; i < n; i++)
        if (e[s][i] && !vis[i])
            closure(i, vis);
}

int main() {
    printf("States: ");
    scanf("%d", &n);

    printf("Epsilon transition matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &e[i][j]);

    printf("Transition matrix (one symbol):\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &t[i][j]);

    for (int i = 0; i < n; i++) {
        int vis[MAX] = {0};
        closure(i, vis);

        for (int j = 0; j < n; j++)
            if (vis[j])
                for (int k = 0; k < n; k++)
                    if (t[j][k])
                        c[i][k] = 1;
    }

    printf("NFA Transition Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%d ", c[i][j]);
        printf("\n");
    }
}