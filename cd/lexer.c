#include <stdio.h>
#include <string.h>
#include <ctype.h>

char *kw[] = {"int", "float", "char", "if", "else", "while", "for",
              "return", "void", "main", "printf", "scanf"};
int nkw = 12;

int isKeyword(char *s) {
    for (int i = 0; i < nkw; i++)
        if (strcmp(s, kw[i]) == 0)
            return 1;
    return 0;
}

int main() {
    char ch, buf[50];
    int i;
    FILE *fp = fopen("input.txt", "r");

    if (!fp) {
        printf("Cannot open input.txt\n");
        return 1;
    }

    while ((ch = fgetc(fp)) != EOF) {
        if (ch == ' ' || ch == '\t' || ch == '\n')
            continue;

        if (isalpha(ch)) {
            i = 0;
            while (isalnum(ch)) {
                buf[i++] = ch;
                ch = fgetc(fp);
            }
            buf[i] = '\0';
            ungetc(ch, fp);

            if (isKeyword(buf))
                printf("Keyword: %s\n", buf);
            else
                printf("Identifier: %s\n", buf);
        }
        else if (isdigit(ch)) {
            i = 0;
            while (isdigit(ch)) {
                buf[i++] = ch;
                ch = fgetc(fp);
            }
            buf[i] = '\0';
            ungetc(ch, fp);
            printf("Number: %s\n", buf);
        }
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' ||
                 ch == '=' || ch == '<' || ch == '>')
            printf("Operator: %c\n", ch);
        else if (ch == '(' || ch == ')' || ch == '{' || ch == '}' ||
                 ch == ';' || ch == ',')
            printf("Symbol: %c\n", ch);
    }

    fclose(fp);
    return 0;
}

/*
Sample Input:
Create a file named "input.txt" in the same directory with contents:

int main() {
    int x = 10;
    printf(x);
}

Expected Output:
Keyword: int
Keyword: main
Symbol: (
Symbol: )
Symbol: {
Keyword: int
Identifier: x
Operator: =
Number: 10
Symbol: ;
Keyword: printf
Symbol: (
Identifier: x
Symbol: )
Symbol: ;
Symbol: }
*/

