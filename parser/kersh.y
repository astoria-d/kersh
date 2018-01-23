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

%token DECL_INT OPE_PLUS OPE_MINUS OPE_MUL OPE_DIV OPE_AND OPE_OR OPE_LS OPE_RS
%token OPE_EQ OPE_GR OPE_GT OPE_LR OPE_LT
%token OPE_INC OPE_DEC OPE_ASIGN OPE_P_ASIGN OPE_M_ASIGN OPE_ML_ASIGN OPE_D_ASIGN OPE_A_ASIGN
%token OPE_O_ASIGN OPE_ARROW DOT QUESTION COLON SEMI_COLON
%token LPAR RPAR

%token INT VAR

%%
code        : /* empty */
            |  code expr        { printf("...ok\n"); }
            ;

expr        : decl_exp
            | asign_exp
            | null_exp
            ;

decl_exp    : DECL_INT VAR SEMI_COLON
            ;

asign_exp   : lval OPE_ASIGN     rval SEMI_COLON
            | lval OPE_P_ASIGN   rval SEMI_COLON
            | lval OPE_M_ASIGN   rval SEMI_COLON
            | lval OPE_ML_ASIGN  rval SEMI_COLON
            | lval OPE_D_ASIGN   rval SEMI_COLON
            | lval OPE_A_ASIGN   rval SEMI_COLON
            | lval OPE_O_ASIGN   rval SEMI_COLON
            ;

null_exp    : rval SEMI_COLON

lval        : VAR
            ;

rval        : lval
            | INT
            | VAR OPE_INC
            | VAR OPE_DEC
            | OPE_INC VAR
            | OPE_DEC VAR
            | func
            | rval OPE_PLUS     rval
            | rval OPE_MINUS    rval
            | rval OPE_MUL      rval
            | rval OPE_DIV      rval
            | rval OPE_AND      rval
            | rval OPE_OR       rval
            | rval OPE_LS       rval
            | rval OPE_RS       rval
            | rval OPE_EQ       rval
            | rval OPE_GR       rval
            | rval OPE_GT       rval
            | rval OPE_LR       rval
            | rval OPE_LT       rval
           ;

func        : VAR  LPAR rval RPAR

%%


/*main func...*/


int main(int argc, char* argv[]) {
    init_values();
    return yyparse();
}
