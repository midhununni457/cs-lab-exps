#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 10

int n;
char prods[MAX][MAX];         // productions: prods[i][0] = LHS, prods[i][1..] = RHS
int first[MAX][128], follow[MAX][128];  // indexed by production index, then ASCII
char nonterms[MAX];
int nn = 0;

int ntIdx(char c) {
    for (int i = 0; i < nn; i++)
        if (nonterms[i] == c) return i;
    return -1;
}

void findFirstUtil(char c, int res[], int visited[]) {
    if (!isupper(c)) {
        res[(int)c] = 1;
        return;
    }

    if (visited[(int)c]) return;
    visited[(int)c] = 1;

    for (int i = 0; i < n; i++) {
        if (prods[i][0] == c) {
            if (prods[i][1] == '#') {
                res[(int)'#'] = 1;
            } else {
                for (int j = 1; prods[i][j]; j++) {
                    int temp[128] = {0};
                    findFirstUtil(prods[i][j], temp, visited);
                    for (int k = 0; k < 128; k++)
                        if (k != '#') res[k] |= temp[k];
                    if (!temp[(int)'#']) break;
                    if (!prods[i][j + 1]) res[(int)'#'] = 1;
                }
            }
        }
    }
    visited[(int)c] = 0;
}

void findFirst(char c, int res[]) {
    int visited[128] = {0};
    findFirstUtil(c, res, visited);
}

void findFollowUtil(char c, int res[], int visited[]) {
    int ci = ntIdx(c);
    if (ci == -1 || visited[(int)c]) return;
    visited[(int)c] = 1;

    if (ci == 0)  // start symbol
        res[(int)'$'] = 1;

    for (int i = 0; i < n; i++) {
        for (int j = 1; prods[i][j]; j++) {
            if (prods[i][j] == c) {
                int k_idx = j + 1;
                int has_epsilon = 1;
                while (prods[i][k_idx]) {
                    int temp[128] = {0};
                    findFirst(prods[i][k_idx], temp);
                    for (int k = 0; k < 128; k++)
                        if (k != '#') res[k] |= temp[k];
                    if (!temp[(int)'#']) {
                        has_epsilon = 0;
                        break;
                    }
                    k_idx++;
                }
                if (has_epsilon && prods[i][0] != c) {
                    findFollowUtil(prods[i][0], res, visited);
                }
            }
        }
    }
}

void findFollow(char c, int res[]) {
    int visited[128] = {0};
    findFollowUtil(c, res, visited);
}

int main() {
    printf("Enter number of productions: ");
    scanf("%d", &n);

    printf("Enter productions (e.g., E=TA, use # for epsilon):\n");
    for (int i = 0; i < n; i++) {
        scanf("%s", prods[i]);
        char lhs = prods[i][0];
        // shift RHS: remove '='
        char temp[MAX];
        strcpy(temp, prods[i] + 2);
        strcpy(prods[i] + 1, temp);

        if (ntIdx(lhs) == -1)
            nonterms[nn++] = lhs;
    }

    printf("\nFirst Sets:\n");
    for (int i = 0; i < nn; i++) {
        int res[128] = {0};
        findFirst(nonterms[i], res);
        printf("First(%c) = { ", nonterms[i]);
        for (int j = 0; j < 128; j++)
            if (res[j]) printf("%c ", j);
        printf("}\n");
    }

    printf("\nFollow Sets:\n");
    for (int i = 0; i < nn; i++) {
        int res[128] = {0};
        findFollow(nonterms[i], res);
        printf("Follow(%c) = { ", nonterms[i]);
        for (int j = 0; j < 128; j++)
            if (res[j]) printf("%c ", j);
        printf("}\n");
    }

    return 0;
}

/*
Sample Input:
Enter number of productions: 5
Enter productions (e.g., E=TA, use # for epsilon):
E=T
E=E+T
T=F
T=T*F
F=i

Expected Output:
First Sets:
First(E) = { i }
First(T) = { i }
First(F) = { i }

Follow Sets:
Follow(E) = { $ + }
Follow(T) = { $ + * }
Follow(F) = { $ + * }
*/
