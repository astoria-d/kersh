%{
#include "kersh.h"
#include "kersh.tab.h"
%}



%%
"+"    return(ADD);
"-"    return(SUB);
"*"    return(MUL);
"/"    return(DIV);
"/n"   return(LF);
[0-9]+ { yylval = atoi(yytext);
       return(NUMBER); }
[ \t]+  ;
.       ;
%%
