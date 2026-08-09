#include <stdio.h>

#define MAX 10

int n, e[MAX][MAX], vis[MAX];

void dfs(int s) {
    vis[s] = 1;
    printf("%d ", s);
    for (int i = 0; i < n; i++)
        if (e[s][i] && !vis[i])
            dfs(i);
}

int main() {
    printf("States: ");
    scanf("%d", &n);

    printf("Enter epsilon transition matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &e[i][j]);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            vis[j] = 0;
        printf("E-Closure(%d): ", i);
        dfs(i);
        printf("\n");
    }
}