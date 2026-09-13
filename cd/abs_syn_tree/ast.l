%{
#include "y.tab.h"
#include <stdlib.h>
%}

%%

[0-9]+  { yylval.val = atoi(yytext); return NUM; }
[a-zA-Z][a-zA-Z0-9]*  { return ID; }
\n      return '\n';
[ \t]   ;
.       return yytext[0];

%%

int yywrap() { return 1; }
