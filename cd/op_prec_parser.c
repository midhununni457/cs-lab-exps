#include <stdio.h>
#include <string.h>

char stack[50], input[50];
int top = -1;
char terminals[] = {'i', '+', '*', '(', ')', '$'};
int nt = 6;

// Operator precedence table
// i + * ( ) $
char table[6][6] = {
    {' ', '>', '>', ' ', '>', '>'},  // i
    {'<', '>', '<', '<', '>', '>'},  // +
    {'<', '>', '>', '<', '>', '>'},  // *
    {'<', '<', '<', '<', '=', ' '},  // (
    {' ', '>', '>', ' ', '>', '>'},  // )
    {'<', '<', '<', '<', ' ', '='}   // $
};

int idx(char c) {
    for (int i = 0; i < nt; i++)
        if (terminals[i] == c)
            return i;
    return -1;
}

void push(char c) { stack[++top] = c; }
char pop() { return stack[top--]; }

int topTerminal() {
    for (int i = top; i >= 0; i--)
        if (idx(stack[i]) != -1)
            return i;
    return 0;
}

int main() {
    printf("Enter input string (end with $): ");
    scanf("%s", input);

    push('$');
    int ip = 0;

    printf("\n%-20s %-20s %-10s\n", "Stack", "Input", "Action");

    while (1) {
        int t = topTerminal();
        char a = stack[t], b = input[ip];

        // Print current state
        stack[top + 1] = '\0';
        printf("%-20s %-20s ", stack, input + ip);

        if (a == '$' && b == '$') {
            printf("Accepted\n");
            break;
        }

        int ai = idx(a), bi = idx(b);
        if (ai == -1 || bi == -1 || table[ai][bi] == ' ') {
            printf("Error\n");
            break;
        }

        if (table[ai][bi] == '<' || table[ai][bi] == '=') {
            push(b);
            ip++;
            printf("Shift %c\n", b);
        } else {
            // Reduce
            printf("Reduce\n");
            if (stack[top] == 'i') {
                pop();
            } else if (top >= 2 && stack[top] == ')' && stack[top - 1] == 'E' && stack[top - 2] == '(') {
                pop();
                pop();
                pop();
            } else if (top >= 2 && stack[top] == 'E' && stack[top - 2] == 'E') {
                pop();
                pop();
                pop();
            } else {
                while (top > 0) {
                    char x = pop();
                    int ti = topTerminal();
                    if (idx(stack[ti]) != -1 && idx(x) != -1 &&
                        table[idx(stack[ti])][idx(x)] == '<') {
                        if (stack[top] == 'E') pop();
                        break;
                    }
                }
            }
            push('E');
        }
    }

    return 0;
}

/*
Sample Input:
Enter input string (end with $): i+i*i$

Expected Output:
Stack                Input                Action    
$                    i+i*i$               Shift i
$i                   +i*i$                Reduce
$E                   +i*i$                Shift +
$E+                  i*i$                 Shift i
$E+i                 *i$                  Reduce
$E+E                 *i$                  Shift *
$E+E*                i$                   Shift i
$E+E*i               $                    Reduce
$E+E*E               $                    Reduce
$E+E                 $                    Reduce
$E                   $                    Accepted
*/
