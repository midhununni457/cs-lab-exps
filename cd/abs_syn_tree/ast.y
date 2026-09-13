%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int yylex();
void yyerror(char *s);

typedef struct node {
    char label[20];
    struct node *left, *right;
} node;

node* mknode(char *label, node *l, node *r) {
    node *n = malloc(sizeof(node));
    strcpy(n->label, label);
    n->left = l;
    n->right = r;
    return n;
}

node* mkleaf(int val) {
    node *n = malloc(sizeof(node));
    sprintf(n->label, "%d", val);
    n->left = n->right = NULL;
    return n;
}

void print_tree(node *n, int depth) {
    if (!n) return;
    for (int i = 0; i < depth; i++) printf("  ");
    printf("%s\n", n->label);
    print_tree(n->left, depth + 1);
    print_tree(n->right, depth + 1);
}

node *root;
%}

%union {
    struct node *nd;
    int val;
}

%token <val> NUM ID
%type <nd> expr term factor

%left '+' '-'
%left '*' '/'

%%

stmt: expr '\n'  { root = $1; print_tree(root, 0); return 0; }
    ;

expr: expr '+' term  { $$ = mknode("+", $1, $3); }
    | expr '-' term  { $$ = mknode("-", $1, $3); }
    | term           { $$ = $1; }
    ;

term: term '*' factor  { $$ = mknode("*", $1, $3); }
    | term '/' factor  { $$ = mknode("/", $1, $3); }
    | factor            { $$ = $1; }
    ;

factor: '(' expr ')'  { $$ = $2; }
      | NUM            { $$ = mkleaf($1); }
      ;

%%

void yyerror(char *s) {
    printf("Error: %s\n", s);
}

int main() {
    printf("Enter expression: ");
    yyparse();
    return 0;
}
