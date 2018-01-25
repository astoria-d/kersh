%{

/*kersh.tab.c*/

#include <stdio.h>
#include "kersh.h"
#include "kersh.tab.h"

%}

%union {
    int ival;
    struct symtab * sym;
}

%token 
DECL_INT OPE_2 OPE_INC OPE_ASIGN
OPE_ARROW DOT QUESTION COLON SEMI_COLON
LPAR RPAR
INT VAR

%%
code        : /* empty */
            |  code expr        { printf("...ok\n"); }
            ;

expr        : decl_exp      SEMI_COLON
            | asign_exp     SEMI_COLON
            | null_exp      SEMI_COLON
            ;

decl_exp    : DECL_INT VAR
            ;

asign_exp   : lval OPE_ASIGN     rval
            ;

null_exp    : rval
            ;

lval        : VAR
            ;

rval        : VAR
            | INT
            | func
            | VAR OPE_INC
            | OPE_INC VAR
            | retval
            ;

retval      : rval OPE_2 VAR
            | rval OPE_2 INT
            | rval OPE_2 func
            | rval OPE_2 OPE_INC VAR
            | rval OPE_2 VAR OPE_INC
            ;

func        : VAR  LPAR rval RPAR

%%


/*main func...*/


int main(int argc, char* argv[]) {
    init_values();
    return yyparse();
}
