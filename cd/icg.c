#include <stdio.h>
#include <string.h>
#include <ctype.h>

int temp = 1;

char expr[50];
int pos = 0;

char lookahead() { return expr[pos]; }

char* E();
char* T();
char* F();

char results[50][10];
int ri = 0;

char* newTemp() {
    sprintf(results[ri], "t%d", temp++);
    return results[ri++];
}

char* F() {
    if (lookahead() == '(') {
        pos++;  // skip (
        char *r = E();
        pos++;  // skip )
        return r;
    } else {
        char *buf = results[ri++];
        buf[0] = lookahead();
        buf[1] = '\0';
        pos++;
        return buf;
    }
}

char* T() {
    char *left = F();
    while (lookahead() == '*' || lookahead() == '/') {
        char op = lookahead();
        pos++;
        char *right = F();
        char *t = newTemp();
        printf("%s = %s %c %s\n", t, left, op, right);
        left = t;
    }
    return left;
}

char* E() {
    char *left = T();
    while (lookahead() == '+' || lookahead() == '-') {
        char op = lookahead();
        pos++;
        char *right = T();
        char *t = newTemp();
        printf("%s = %s %c %s\n", t, left, op, right);
        left = t;
    }
    return left;
}

int main() {
    char id[10];

    printf("Enter expression (e.g., a=b+c*d): ");
    scanf("%s", expr);

    // Extract LHS variable
    id[0] = expr[0];
    id[1] = '\0';
    pos = 2;  // skip 'a='

    printf("\nThree Address Code:\n");
    char *result = E();
    printf("%s = %s\n", id, result);

    return 0;
}

/*
Sample Input:
Enter expression (e.g., a=b+c*d): a=b+c*d

Expected Output:
Three Address Code:
t1 = c * d
t2 = b + t1
a = t2

Sample Input 2:
a=b+c*d-e/f

Expected Output:
t1 = c * d
t2 = b + t1
t3 = e / f
t4 = t2 - t3
a = t4
*/
