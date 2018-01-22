%{

/*kersh.tab.c*/

#include <stdio.h>
#include "kersh.h"
#include "kersh.tab.h"

%}



%token NUMBER
%left ADD SUB
%left MUL DIV
%%
list : /* empty */
     | list expr        { printf("answer: %d\n",$2); }
     ;
expr : expr ADD expr    { $$ = $1 + $3; }
     | expr SUB expr    { $$ = $1 - $3; }
     | expr MUL expr    { $$ = $1 * $3; }
     | expr DIV expr    { $$ = $1 / $3; }
     | NUMBER
     ;


%%


/*main func...*/


int main(int argc, char* argv[]) {
    /*yydebug = 1;*/
    return yyparse();
}
