#include <stdio.h>
#include <string.h>

int main() {
    int n, i;
    char op[5], arg1[10], arg2[10], result[10];

    printf("Enter number of three address codes: ");
    scanf("%d", &n);

    printf("Enter three address codes (result = arg1 op arg2):\n");
    printf("(For assignment, use: result = arg1)\n\n");

    char lines[50][100];
    for (i = 0; i < n; i++) {
        do {
            if (!fgets(lines[i], sizeof(lines[i]), stdin)) break;
        } while (lines[i][0] == '\n' || lines[i][0] == '\r');
    }

    printf("\n8086 Assembly Code:\n\n");

    for (i = 0; i < n; i++) {
        int tokens = sscanf(lines[i], "%s = %s %s %s", result, arg1, op, arg2);

        if (tokens == 2 || (tokens == 4 && strcmp(op, "=") == 0)) {
            // Simple assignment: result = arg1 (supports both "a = t2" and "a = t2 = _")
            printf("MOV %s, %s\n", result, arg1);
        }
        else if (tokens == 4 && strcmp(op, "+") == 0) {
            printf("MOV AX, %s\n", arg1);
            printf("ADD AX, %s\n", arg2);
            printf("MOV %s, AX\n", result);
        }
        else if (tokens == 4 && strcmp(op, "-") == 0) {
            printf("MOV AX, %s\n", arg1);
            printf("SUB AX, %s\n", arg2);
            printf("MOV %s, AX\n", result);
        }
        else if (tokens == 4 && strcmp(op, "*") == 0) {
            printf("MOV AX, %s\n", arg1);
            printf("MUL %s\n", arg2);
            printf("MOV %s, AX\n", result);
        }
        else if (tokens == 4 && strcmp(op, "/") == 0) {
            printf("MOV AX, %s\n", arg1);
            printf("DIV %s\n", arg2);
            printf("MOV %s, AX\n", result);
        }
        printf("\n");
    }

    return 0;
}

/*
Sample Input:
Enter number of three address codes: 3
Enter three address codes (result = arg1 op arg2):
t1 = c * d
t2 = b + t1
a = t2

Expected Output:
8086 Assembly Code:

MOV AX, c
MUL d
MOV t1, AX

MOV AX, b
ADD AX, t1
MOV t2, AX

MOV a, t2
*/
