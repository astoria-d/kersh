%{
#include "kersh.h"
#include "kersh.tab.h"
%}



%%
[ \t\r\n]+      ; /*ignore white spaces...*/
"+"         {    printf("plus\n");      return(ADD);   }
"-"         {    printf("minus\n");     return(SUB);   }
"*"         {    printf("mul\n");       return(MUL);   }
"/"         {    printf("div\n");       return(DIV);   }
[0-9]+      {    printf("num\n");       yylval = atoi(yytext);     return(NUMBER); }
%%


int main2(int argc, char* argv[]) {
    return yylex();
}

