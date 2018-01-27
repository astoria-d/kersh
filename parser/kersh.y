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
OPE_2 OPE_INC OPE_ASIGN
OPE_ARROW DOT COMMA QUESTION COLON SEMI_COLON
LPAR RPAR LBRACE RBRACE LBRACKET RBRACKET
TYPEDEF SIZEOF ENUM STRUCT UNION
CONST STATIC EXTERN VOLATILE INLINE
DO WHILE FOR CONTINUE BREAK
GOTO RETURN
SWITCH CASE DEFAULT
IF ELSE
VOID INT CHAR SHORT LONG SIGN VAR

%left OPE_2


%%
code        : /* empty */
            |  code expr        { printf("...ok\n"); }
            ;

expr        : decl_exp      SEMI_COLON
            | asign_exp     SEMI_COLON
            | null_exp      SEMI_COLON
            ;

decl_exp    :   all_type var_list
            ;

asign_exp   : lval OPE_ASIGN     rval
            ;

null_exp    : rval
            ;

lval        : VAR
            ;

rval        : VAR
            | INT
            | func_call
            | VAR OPE_INC
            | OPE_INC VAR
            | LPAR rval RPAR
            | rval OPE_2 rval
            ;

func_call   : VAR  LPAR rval RPAR


var_list    :   VAR
            |   var_list COMMA VAR
            ;

/*variable definition rules...*/
all_type        :   base_type
                |   derived_type
                ;

base_type       :   unit_type
                |   SIGN  unit_type
                ;

unit_type       :   CHAR
                |   SHORT
                |   LONG
                |   INT
                |   SHORT INT
                |   LONG INT
                |   LONG LONG
                |   LONG LONG INT
                ;

derived_type    :   VAR
                ;

%%


/*main func...*/


int main(int argc, char* argv[]) {
    init_values();
    return yyparse();
}
