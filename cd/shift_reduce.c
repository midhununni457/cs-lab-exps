#include <stdio.h>
#include <string.h>

#define MAX 20

char stack[MAX][MAX], input[MAX][MAX];
int top = -1, ip = 0, ni;

char grammar[MAX][MAX];
int ng;

void push(char *s) { strcpy(stack[++top], s); }
void pop() { top--; }

void getStackStr(char *str) {
    str[0] = '\0';
    for (int i = 0; i <= top; i++) {
        strcat(str, stack[i]);
        if (i < top) strcat(str, " ");
    }
}

void getInputStr(char *str) {
    str[0] = '\0';
    for (int i = ip; i < ni; i++) {
        strcat(str, input[i]);
        if (i < ni - 1) strcat(str, " ");
    }
}

int main() {
    printf("Enter number of grammar rules: ");
    scanf("%d", &ng);

    printf("Enter grammar (e.g., E=a+b):\n");
    for (int i = 0; i < ng; i++)
        scanf("%s", grammar[i]);

    printf("Enter number of input tokens: ");
    scanf("%d", &ni);

    printf("Enter input tokens (end with $):\n");
    for (int i = 0; i < ni; i++)
        scanf("%s", input[i]);

    push("$");

    char start_lhs[MAX];
    sscanf(grammar[0], "%[^=]", start_lhs);

    printf("\n%-25s %-25s %-15s\n", "Stack", "Input", "Action");

    while (1) {
        char sStr[100], inStr[100];
        getStackStr(sStr);
        getInputStr(inStr);
        printf("%-25s %-25s ", sStr, inStr);

        // Check if done
        if (top == 1 && strcmp(stack[top], start_lhs) == 0 &&
            ip == ni - 1 && strcmp(input[ip], "$") == 0) {
            printf("Accepted\n");
            break;
        }

        // Try to reduce
        int reduced = 0;
        for (int g = 0; g < ng; g++) {
            // Extract RHS
            char lhs[MAX], rhs[MAX];
            sscanf(grammar[g], "%[^=]=%s", lhs, rhs);

            // Tokenize RHS
            char rtokens[MAX][MAX];
            int nr = 0;
            for (int i = 0; rhs[i]; i++) {
                char tmp[2] = {rhs[i], '\0'};
                strcpy(rtokens[nr++], tmp);
            }

            // Check if top of stack matches RHS
            if (nr <= top + 1) {
                int match = 1;
                for (int i = 0; i < nr; i++) {
                    if (strcmp(stack[top - nr + 1 + i], rtokens[i]) != 0) {
                        match = 0;
                        break;
                    }
                }
                if (match) {
                    top -= nr;
                    push(lhs);
                    printf("Reduce %s->%s\n", lhs, rhs);
                    reduced = 1;
                    break;
                }
            }
        }

        if (!reduced) {
            if (ip < ni && strcmp(input[ip], "$") != 0) {
                printf("Shift %s\n", input[ip]);
                push(input[ip]);
                ip++;
            } else {
                printf("Error\n");
                break;
            }
        }
    }

    return 0;
}

/*
Sample Input:
Enter number of grammar rules: 3
Enter grammar (e.g., E=a+b):
E=E+E
E=E*E
E=i
Enter number of input tokens: 6
Enter input tokens (end with $):
i + i * i $

Expected Output:
$                   i + i * i $         Shift i
$ i                 + i * i $           Reduce E->i
$ E                 + i * i $           Shift +
$ E +               i * i $             Shift i
$ E + i             * i $               Reduce E->i
$ E + E             * i $               Shift *
$ E + E *           i $                 Shift i
$ E + E * i         $                   Reduce E->i
$ E + E * E         $                   Reduce E->E*E
$ E + E             $                   Reduce E->E+E
$ E                 $                   Accepted
*/
