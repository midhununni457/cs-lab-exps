%{
#include "y.tab.h"
#include <stdlib.h>
extern int yylval;
%}

%%

[0-9]+  { yylval = atoi(yytext); return NUM; }
\n      return '\n';
.       return yytext[0];

%%

int yywrap() { return 1; }
